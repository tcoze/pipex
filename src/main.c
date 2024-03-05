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

static int	first_fork(struct s_cmd *cmd, char **envp)
{
	if (cmd->f_path != NULL && cmd->f1 >= 0)
	{
		cmd->pid1 = fork();
		if (cmd->pid1 == -1)
		{
			if (cmd->f2 >= 0)
				close(cmd->f2);
			return (close(cmd->f1), -1);
		}
		if (cmd->pid1 == 0)
			if (child_process(cmd, envp) == -1)
				return (-1);
	}
	return (0);
}

static int	second_fork(struct s_cmd *cmd, char **envp)
{
	if (cmd->s_path != NULL && cmd->f2 >= 0)
	{
		cmd->pid2 = fork ();
		if (cmd->pid2 == -1)
		{
			if (cmd->f2 >= 0)
				close(cmd->f2);
			return (-1);
		}
		if (cmd->pid2 == 0)
			if (parent_process(cmd, envp) == -1)
				return (-1);
	}
	return (0);
}

static void	first_fill(struct s_cmd *cmd)
{
	cmd->first = NULL;
	cmd->f_path = NULL;
	cmd->second = NULL;
	cmd->s_path = NULL;
	cmd->pfd[0] = 0;
	cmd->pfd[1] = 0;
	cmd->pid1 = 0;
	cmd->pid2 = 0;
}

int	pipex(struct s_cmd *cmd, char **envp)
{
	int		status;

	if ((cmd->s_path != NULL || cmd->f_path != NULL) && pipe(cmd->pfd) == -1)
	{
		if (cmd->f1 >= 0)
			close(cmd->f1);
		if (cmd->f2 >= 0)
			close(cmd->f2);
		return (-1);
	}
	if (first_fork(cmd, envp) == -1)
		return (-1);
	if (double_close(cmd->f1, cmd->pfd[1]) == -1)
		return (-1);
	if (second_fork(cmd, envp) == -1)
		return (-1);
	if (cmd->pid1 != 0)
		waitpid(cmd->pid1, &status, 0);
	if (cmd->pid2 != 0)
		waitpid(cmd->pid2, &status, 0);
	if (double_close(cmd->f2, cmd->pfd[0]) == -1)
		return (-1);
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
