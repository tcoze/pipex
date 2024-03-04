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

/*#include <sys/stat.h>
static void print_fd(void)
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

int	pipex(struct s_cmd *cmd, char **envp)
{
	pid_t	pid1;
	int		status;
	int		pfd[2];


	if ((cmd->s_path != NULL || cmd->f_path) && cmd->f2 && pipe(pfd) == -1)
	{
		if (cmd->f1 >= 0)
			close(cmd->f1);
		if (cmd->f2 >= 0)
			close (cmd->f2);
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
		close(cmd->f1);
	}
	if (cmd->s_path != NULL && cmd->f2 >= 0)
	{
		if (parent_process (cmd, envp, pfd) == -1)
			return (-1);
		close(cmd->f2);
		if (cmd->first != NULL)
			while (errno != ECHILD)
				waitpid (pid1, &status, 0);
	}
	if (cmd->f1 >= 0)
		close(cmd->f1);
	if (cmd->f2 >= 0)
		close(cmd->f2);
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_cmd	cmd;

	cmd.first = NULL;
	cmd.f_path = NULL;
	cmd.second = NULL;
	cmd.s_path = NULL;
	if (argc != 5)
		return (ft_printf (2, "Put only 5 arguments\n"), -1);
	cmd.f2 = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);  // FILE 2 OPEN ICI
	cmd.f1 = open (argv[1], O_RDONLY);  // FILE 1 OPEN ICI
	if (cmd.f1 < 0)
		ft_printf (2, "%s: No such file or directory\n", argv[1]);
	if (parsing(argv, envp, &cmd) == -1) // PARSING CMD
	{
		if (cmd.f1 >= 0)
			close(cmd.f1);
		return (close(cmd.f2), -1);
	}
	if (cmd.second == NULL)
	{
		if (cmd.f1 >= 0)
			close(cmd.f1);
		if (cmd.f2 >= 0)
			close(cmd.f2);
		return (clear_struct (&cmd), 0);
	}
	if (pipex(&cmd, envp) == -1)
		return (clear_struct(&cmd), -1);
	return (clear_struct(&cmd), 0);
}