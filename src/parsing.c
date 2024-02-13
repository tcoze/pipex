/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:00:38 by tcoze             #+#    #+#             */
/*   Updated: 2024/02/10 17:11:23 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <stdio.h>

static char	*ft_absolute_path(char *cmd)
{
	if (ft_strchr_str(cmd, "/"))
	{
		if (access(cmd, F_OK) == -1)
			return (NULL);
		else
			return (cmd);
	}
	return (NULL);
}

static char	**ft_find_path(char **envp, char **path)
{
	int		i;
	char	*p_find;

	i = 0;
	while (envp[i] != NULL)
	{
		while (envp[i][0] != 'P')
			i++;
		if (ft_strchr_str(envp[i], "PATH=") != NULL)
		{
			p_find = ft_strchr_str(envp[i], "PATH=");
			path = ft_split(p_find, ':');
			if (path == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	return (path);
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
	if (ft_absolute_path(cmd) != NULL)
		return (cmd);
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
	if (argc != 5)
		return (perror("not enought arguments"), -1);
	if (ft_check_file(argv[1], argv[4]) == -1)
		return (perror("Can't open/read file1"), -1);
	if (ft_check_file(argv[1], argv[4]) == -2)
		return (perror("Can't open/read file2"), -1);
	if (ft_check_cmd(argv[2], envp) == NULL)
	{
		if (ft_check_cmd(argv[2], envp) == NULL)
			return (perror("Command1 not found"), -1);
		return (perror("unexpected error"), -1);
	}
	if (ft_check_cmd(argv[3], envp) == NULL)
	{
		if (ft_check_cmd(argv[3], envp) == NULL)
			return (perror("Command2 not found"), -1);
		return (perror("unexpected error"), -1);
	}
	return (0);
}
