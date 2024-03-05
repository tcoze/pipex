/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:27:43 by tcoze             #+#    #+#             */
/*   Updated: 2024/03/05 13:43:06 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

static void first_fill(struct s_cmd *cmd)
{
	cmd->first = NULL;
	cmd->f_path = NULL;
	cmd->second = NULL;
	cmd->s_path = NULL;
}

int	pipex(struct s_cmd *cmd, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		pfd[2];

	pfd[0] = 0;
	pfd[1] = 0;
	pid1 = 0;
	pid2 = 0;
	if ((cmd->s_path != NULL || cmd->f_path != NULL) && pipe(pfd) == -1)
	{
		if (cmd->f1 >= 0)
			close(cmd->f1);
		if (cmd->f2 >= 0)
			close(cmd->f2);
		return (-1);
	}
	if (cmd->f_path != NULL && cmd->f1 >= 0)
	{
		pid1 = fork ();
		if (pid1 == -1)
		{
			if (cmd->f2 >= 0)
				close(cmd->f2);
			return (close(cmd->f1), -1);
		}
		if (pid1 == 0)
			if (child_process(cmd, envp, pfd) == -1)
				return (-1);
	}
	if (cmd->f1 >= 0)
		close(cmd->f1);
	if (pfd[1] >= 0)
		close(pfd[1]);
	if (cmd->s_path != NULL && cmd->f2 >= 0)
	{
		pid2 = fork ();
		if (pid2 == -1)
		{
			if (cmd->f2 >= 0)
				close(cmd->f2);
			return (-1);
		}
		if (pid2 == 0)
			if (parent_process(cmd, envp, pfd) == -1)
				return (-1);
	}
	if (pid1 != 0)
		waitpid(pid1, &status, 0);
	if (pid2 != 0)
		waitpid(pid2, &status, 0);
	if (cmd->f2 >= 0)
		close(cmd->f2);
	if (pfd[0] >= 0)
		close(pfd[0]);
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_cmd	cmd;
	first_fill(&cmd);
	if (argc != 5)
		return (ft_printf (2, "Put only 5 arguments\n"), -1);
	cmd.f2 = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (envp == NULL)
	{
		if (cmd.f2 >= 0)
			return (close(cmd.f2), -1);
		return (-1);
	}
	cmd.f1 = open (argv[1], O_RDONLY);
	if (cmd.f1 < 0)
		ft_printf (2, "%s: No such file or directory\n", argv[1]);
	if (parsing(argv, envp, &cmd) == -1)
	{
		if (cmd.f1 >= 0)
			close(cmd.f1);
		return (close(cmd.f2), -1);
	}
	if (pipex(&cmd, envp) == -1)
		return (clear_struct (&cmd), -1);
	return (clear_struct(&cmd), 0);
}
