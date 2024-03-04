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
//#include <sys/stat.h>


/*static void print_fd(void)
{
	int i = 0;
	struct stat s;
	while (i < 1024)
	{
		if (!fstat(i, &s))
			dprintf(2, "fd open = %d\n", i);
		i++;
	}
}*/

int	child_process(struct s_cmd *cmd, char **envp, int *pfd)
{
	if (cmd->f1 >= 0 && cmd->f_path && cmd->first)
	{
		if (dup2(cmd->f1, STDIN_FILENO) < 0)
			return (close(cmd->f1), -1);
		if (dup2(pfd[STDOUT_FILENO], STDOUT_FILENO) < 0)
			return (close(cmd->f1), -1);
		if (close(pfd[STDIN_FILENO]) == -1)
			return (close(pfd[STDOUT_FILENO]), close (cmd->f1), -1);
		if (close(pfd[STDOUT_FILENO]) == -1)
			return (close (cmd->f1), -1);
		if (close(cmd->f1) == -1)
			return (-1);
		if (close(cmd->f2) >= 0)
			close(cmd->f2);
		if (execve (cmd->f_path, cmd->first, envp) == -1)
			return (close (0), close (1), -1);
	}
	else
	{
		if (close(cmd->f1) == -1)
			return (close(cmd->f2), -1);
		if (close(cmd->f2) >= 0)
			close(cmd->f2);
	}
	return (0);
}

int	parent_process(struct s_cmd *cmd, char **envp, int *pfd)
{
	if (cmd->s_path && cmd->second)
	{
		if (cmd->f2 >= 0)
		{
			if (dup2 (cmd->f2, STDOUT_FILENO) < 0)
				return (close (cmd->f2), -1);
			if (dup2 (pfd[STDIN_FILENO], STDIN_FILENO) < 0)
				return (close (cmd->f2), -1);
			if (close (pfd[STDOUT_FILENO]) == -1)
				return (close (pfd[STDIN_FILENO]), close (cmd->f2), -1);
			if (close (pfd[STDIN_FILENO]) == -1)
				return (close (cmd->f2), -1);
			if (close (cmd->f2) == -1)
				return (-1);
		}
//		print_fd();
//		dprintf(2, "f2 : %d\n", cmd->f2);
		if (execve(cmd->s_path, cmd->second, envp) == -1)
			return (close (0), close (1), -1);
	}
	else
		if (close(cmd->f2) >= 0)
			close(cmd->f2);
	return (0);
}
