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
#include <errno.h>

int	ft_count_path(char **path)
{
	int	i;

	i = 0;
	if (path[0] == NULL)
		return (0);
	while (path[i] != NULL)
		i++;
	return (i);
}

int	pipex(int f1, struct s_cmd cmd, char **envp, char **argv)
{
	pid_t	pid1;
	int		status;
	int		f2;
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
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 < 0)
		return (-1);
	if (parent_process(f2, cmd, envp, pfd) == -1)
		return (close(f2), -1);
	while (errno != ECHILD)
		waitpid(pid1, &status, 0);
	return (close(f2), 0);
}

int	main(int argc, char *argv[], char **envp)
{
	int		f1;
	t_cmd	cmd;

	if (check_parsing(argc, argv, envp) == -1)
		return (-1);
	f1 = open(argv[1], O_RDONLY);
	if (f1 < 0)
		return (-1);
	cmd.first = ft_split(argv[2], ' ');
	cmd.f_path = ft_check_cmd(argv[2], envp);
	cmd.second = ft_split(argv[3], ' ');
	cmd.s_path = ft_check_cmd(argv[3], envp);
	if (pipex(f1, cmd, envp, argv) == -1)
		return (-1);
	return (0);
}
