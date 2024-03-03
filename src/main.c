/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:27:43 by tcoze             #+#    #+#             */
/*   Updated: 2024/03/02 10:27:43 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

int	pipex(int f1, struct s_cmd *cmd, char **envp, int f2)
{
	pid_t	pid1;
	int		status;
	int		pfd[2];


	if (pipe(pfd) == -1)
		return (close(f1), -1);
	if (cmd->first != NULL)
	{
		pid1 = fork ();
		if (pid1 == -1)
			return (close(f1), close(pfd[0]), close (pfd[1]), -1);
		if (pid1 == 0)
			if (child_process (f1, cmd, envp, pfd) == -1)
				return (close (f1), close(pfd[0]), close (pfd[1]), -1);
	}
	close(f1);
	if (cmd->second != NULL)
	{
		if (parent_process (f2, cmd, envp, pfd) == -1)
			return (close(f2), -1);
		if (cmd->first != NULL)
			while (errno != ECHILD)
				waitpid (pid1, &status, 0);
	}
	return (close(pfd[0]), close(pfd[1]), close(f2), 0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_cmd	cmd;
	int		f1;
	int 	f2;

	setbuf(stdout, NULL);
	cmd.first = NULL;
	cmd.f_path = NULL;
	cmd.second = NULL;
	cmd.s_path = NULL;
	if (argc != 5)
		return (ft_printf (2, "Put only 5 arguments\n"), -1);
	f2 = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);  // FILE 2 OPEN ICI
	if (f2 < 0)
		return (-1);
	f1 = open (argv[1], O_RDONLY);  // FILE 1 OPEN ICI
	if (f1 < 0)
		ft_printf (2, "%s: No such file or directory\n", argv[1]);
	if (parsing(argv, envp, &cmd) == -1) // PARSING CMD
		return (close(f1), close(f2), -1);
	if (pipex(f1, &cmd, envp, f2) == -1)
		return (close(f2), clear_struct(&cmd), close(f1), -1);
	return (close(f2), close(f1), clear_struct(&cmd), 0);
}