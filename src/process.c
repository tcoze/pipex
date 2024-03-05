/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logname <logname@student.1337.ma.          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:10:49 by logname           #+#    #+#             */
/*   Updated: 2024/02/05 18:33:38 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

static void	print_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "sudo", 4) == 0 || ft_strncmp(cmd, "SUDO", 4) == 0)
		ft_printf(2, "/usr/bin/sudo: Permission denied\n");
	else
		ft_printf(2, "Command not found : %s\n", cmd);
}

int	child_process(struct s_cmd *cmd, char **envp)
{
	if (cmd->f_path && cmd->f1 >= 0)
	{
		if (dup2(cmd->f1, STDIN_FILENO) < 0)
			return (close(cmd->f1), -1);
		if (dup2(cmd->pfd[1], STDOUT_FILENO) < 0)
			return (close(cmd->f1), -1);
		if (close(cmd->pfd[0]) == -1)
			return (close(cmd->pfd[1]), close (cmd->f1), -1);
		if (close(cmd->pfd[1]) == -1)
			return (close(cmd->f1), -1);
		if (close(cmd->f1) == -1)
			return (-1);
		if (cmd->f2 >= 0)
			close(cmd->f2);
		if (execve(cmd->f_path, cmd->first, envp) == -1)
			return (print_cmd(cmd->first[0]), -1);
	}
	if (cmd->f1 >= 0)
		close(cmd->f1);
	if (cmd->f2 >= 0)
		close(cmd->f2);
	return (0);
}

int	parent_process(struct s_cmd *cmd, char **envp)
{
	if (cmd->s_path && cmd->f2 >= 0)
	{
		if (dup2(cmd->f2, STDOUT_FILENO) < 0)
			return (close(cmd->f2), -1);
		if (dup2(cmd->pfd[0], STDIN_FILENO) < 0)
			return (close(cmd->f2), -1);
		if (close(cmd->pfd[0]) == -1)
			return (close(cmd->f2), -1);
		if (close(cmd->f2) == -1)
			return (-1);
		if (cmd->f1 >= 0)
			close(cmd->f1);
		if (execve(cmd->s_path, cmd->second, envp) == -1)
			return (print_cmd(cmd->second[0]), -1);
	}
	else
		if (cmd->f2 >= 0)
			close(cmd->f2);
	return (0);
}
