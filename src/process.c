/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logname <logname@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:10:49 by logname           #+#    #+#             */
/*   Updated: 2024/02/05 18:33:38 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process(int f1, struct s_cmd cmd, char **envp, int *pfd)
{
	if (dup2 (f1, STDIN_FILENO) < 0)
		return (-1);
	if (dup2 (pfd[STDOUT_FILENO], STDOUT_FILENO) < 0)
		return (-1);
	if (close(pfd[STDIN_FILENO]) == -1)
		return (close(pfd[STDOUT_FILENO]), close(f1), -1);
	if (close(pfd[STDOUT_FILENO]) == -1)
		return (close(f1), -1);
	close(f1);
	if (execve(cmd.f_path, cmd.first, envp) == -1)
		return (-1);
	return (0);
}

int	parent_process(int f2, struct s_cmd cmd, char **envp, int *pfd)
{
	if (dup2 (pfd[STDIN_FILENO], STDIN_FILENO) < 0)
		return (-1);
	if (dup2 (f2, STDOUT_FILENO) < 0)
		return (-1);
	if (close(pfd[STDOUT_FILENO]) == -1)
		return (close(pfd[STDIN_FILENO]), close(f2), -1);
	if (close(pfd[STDIN_FILENO]) == -1)
		return (close(f2), -1);
	close(f2);
	if (execve(cmd.s_path, cmd.second, envp) == -1)
		return (-1);
	return (0);
}
