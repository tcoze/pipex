/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:00:38 by tcoze             #+#    #+#             */
/*   Updated: 2024/02/20 17:37:04 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

static char	*ft_absolute_path(char	*cmd)
{
	if (access(cmd, F_OK) == -1)
		return (NULL);
	return (cmd);
}

static char	**ft_find_path(char **envp, char **path)
{
	int		i;
	char	*p_find;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr_str(envp[i], "PATH=") != NULL
			&& ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			p_find = ft_strchr_str(envp[i], "PATH=");
			path = ft_split(p_find, ':');
			if (path == NULL)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static int	ft_check_file(char *file1, char *file2)
{
	int	fd1;
	int	fd2;

	fd1 = open(file1, O_RDONLY);
	if (fd1 == -1)
		return (-1);
	fd2 = open(file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd2 == -1)
		return (-2);
	close(fd1);
	close(fd2);
	return (0);
}

char	*ft_check_cmd(char *cmd, char **envp)
{
	int		i;
	char	**target;
	char	**path;
	char	*str;

	i = 0;
	path = NULL;
	if (cmd[0] == '/')
		return (ft_absolute_path(cmd));
	path = ft_find_path(envp, path);
	if (path == NULL)
		return (NULL);
	while (path[i] != NULL)
	{
		str = ft_strjoin (path[i], "/");
		target = ft_split (cmd, ' ');
		str = ft_strjoin(str, target[0]);
		if (access (str, F_OK) == -1)
			i++;
		else
			return (str);
	}
	return (NULL);
}

int	check_parsing(int argc, char *argv[], char **envp)
{
	int	i;

	i = 0;
	if (argc != 5)
		return (ft_printf("not enough arguments\n"), -1);
	if (ft_strncmp(argv[2], "sudo", 4) == 0
		|| ft_strncmp(argv[3], "sudo", 4) == 0)
		ft_printf("/usr/bin/sudo: Permission denied\n", i++);
	if (ft_check_file(argv[1], argv[4]) == -1)
		ft_printf("%s: No such file or directory\n", argv[1], i++);
	if (ft_check_file(argv[1], argv[4]) == -2)
		ft_printf("%s: Couldn't create file or directory\n", argv[4], i++);
	if (ft_check_cmd(argv[2], envp) == NULL)
		ft_printf("%s: command not found\n", argv[2], i++);
	if (ft_check_cmd(argv[3], envp) == NULL)
		ft_printf("%s: command not found\n", argv[3], i++);
	if (i > 0)
		return (-1);
	return (0);
}
