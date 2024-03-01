/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:00:09 by tcoze             #+#    #+#             */
/*   Updated: 2024/01/29 09:00:28 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

static int	ft_file_one(struct s_cmd cmd, char **envp, int f2)
{
	if (dup2 (f2, STDOUT_FILENO) < 0)
		return (close(f2), clear_struct(cmd), -1);
	if (close(f2) == -1)
		return (clear_struct(cmd), -1);
	if (execve(cmd.s_path, cmd.second, envp) == -1)
		return (clear_struct(cmd), close(f2), -1);
	return (close(f2), clear_struct(cmd), 0);
}

int	pipex(int f1, struct s_cmd cmd, char **envp, int f2)
{
	pid_t	pid1;
	int		status;
	int		pfd[2];

	if (pipe(pfd) == -1)
		return (close(f1), -1);
	pid1 = fork();
	if (pid1 == -1)
		return (close(f1), -1);
	if (pid1 == 0)
		if (child_process (f1, cmd, envp, pfd) == -1)
			return (close(f1), -1);
	close(f1);
	if (parent_process(f2, cmd, envp, pfd) == -1)
		return (close(f2), -1);
	while (errno != ECHILD)
		waitpid(pid1, &status, 0);
	return (close(f2), 0);
}

int	main(int argc, char *argv[], char **envp)
{
	int f1;
	int f2;
	t_cmd cmd;
	if (argc != 5)
		return (ft_printf (2, "not enough arguments\n"), -1);
	f2 = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 < 0)
		return (-1);
	if (ft_strncmp(argv[2], "sudo", 4) == 0
		|| ft_strncmp(argv[3], "sudo", 4) == 0)
		ft_printf(2, "/usr/bin/sudo: Permission denied\n");
	if (argv[3][0] == '\0')
		return (close (f2), ft_printf (2, """: command not found\n"), -1);
	if (argv[2][0] != '\0')
	{
		cmd.first = ft_split (argv[2], ' ');
		if (cmd.first == NULL)
			return (close (f2), -1);
		cmd.f_path = ft_check_cmd (argv[2], envp);
		if (cmd.f_path == NULL)
			return (close (f2), clear_struct (cmd), -1);
	}
	if (argv[3][0] != '\0')
	{
		if (ft_strchr_str (argv[3], " ") != NULL)
		{
			ft_printf (1, "OLALLALALALLA\n");
			cmd.second = ft_split (argv[3], ' ');
			if (cmd.second == NULL)
				return (close (f2), clear_struct (cmd), -1);
		}
		cmd.s_path = ft_check_cmd (argv[3], envp);
		ft_printf (1, "AIEIIEIEIEIE\n");
		if (cmd.s_path == NULL)
			return (close (f2), clear_struct (cmd), -1);
	}
	f1 = open(argv[1], O_RDONLY);
	if (f1 < 0 || argv[2][0] == '\0')
	{
		if (f1 < 0)
			ft_printf(2, "%s: No such file or directory\n", argv[1]);
		if (f1 >= 0)
			close(f1);
		if (ft_file_one(cmd, envp, f2) == -1)
			return (close (f2), -1);
		return (close(f2), 0);
	}
	if (pipex(f1, cmd, envp, f2) == -1)
		return (close(f2), clear_struct(cmd), close(f1), -1);
	return (close (f2), clear_struct(cmd), 0);
}
