/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:44:02 by tcoze             #+#    #+#             */
/*   Updated: 2024/03/05 13:44:02 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (cmd->f_path && cmd->f1 >= 0)
	{
		if (dup2 (cmd->f1, STDIN_FILENO) < 0)
			return (close (cmd->f1), -1);
		if (dup2 (pfd[1], STDOUT_FILENO) < 0)
			return (close (cmd->f1), -1);
		if (close (pfd[0]) == -1)
			return (close (pfd[1]), close (cmd->f1), -1);
		if (close (pfd[1]) == -1)
			return (close (cmd->f1), -1);
		if (close (cmd->f1) == -1)
			return (-1);
		if (close (cmd->f2) >= 0)
			close (cmd->f2);
		if (execve (cmd->f_path, cmd->first, envp) == -1)
			return (close (0), close (1), dprintf (2, "Command not found : %s\n", cmd->first[0]), -1);
	}
	if (cmd->f1 >= 0)
		close(cmd->f1);
	if (cmd->f2 >= 0)
		close(cmd->f2);
	return (0);
}

int	parent_process(struct s_cmd *cmd, char **envp, int *pfd)
{
	if (cmd->s_path && cmd->f2 >= 0)
	{
		if (dup2(cmd->f2, STDOUT_FILENO) < 0)
			return (close (cmd->f2), -1);
		if (dup2(pfd[0], STDIN_FILENO) < 0)
			return (close (cmd->f2), -1);
		//if (close(pfd[1]) == -1)
		//	return (close (pfd[0]), close (cmd->f2), -1);
		if (close(pfd[0]) == -1)
			return (close (cmd->f2), -1);
		if (close(cmd->f2) == -1)
			return (-1);
		if (cmd->f1 >= 0)
			close(cmd->f1);
		if (execve(cmd->s_path, cmd->second, envp) == -1)
			return (close(0), close(1), close (2), dprintf (2, "Command not found : %s\n", cmd->first[0]), -1);
	}
	else
		if (cmd->f2 >= 0)
			close(cmd->f2);
	return (0);
}
