/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:46:07 by tcoze             #+#    #+#             */
/*   Updated: 2024/02/27 14:46:07 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

char	*ft_check_access(char *str2)
{
	if (access (str2, F_OK) == -1)
		return (NULL);
	else
		return (str2);
}

static int	check_absolute_path(char *argv, char **cmd, char *cmd_path)
{
	int		i;

	i = 0;
	if (ft_strchr_str (argv, "/"))
	{
		if (ft_check_access(argv) != NULL)
		{
			cmd_path = ft_strjoin(cmd_path, argv);
			if (cmd_path == NULL)
				return (-1);
			temp = ft_split(argv, '/');
			if (temp == NULL)
				return (-1);
			i = ft_count_path(temp);
			cmd = ft_split(temp[i], ' ');
			if (cmd == NULL)
				return (-1);
			ft_freeall(temp, i);
			return (1);
		}
		if (ft_check_access(argv) == NULL)
		{
			temp = ft_split(argv, '/');
			if (temp == NULL)
				return (-1);
			i = ft_count_path(temp);
			ft_printf(2, "%s: command not found\n", temp[i]);
			ft_freeall(temp, i);
			return (2);
		}
	}
	return (0);
}

char	**ft_find_path(char **envp, char **path)
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
				return (free(p_find), NULL);
			return (path);
		}
		i++;
	}
	return (ft_freeall(path, ft_count_path(path)), NULL);
}


/*char	*ft_check_cmd(char *cmd, char **envp)
{
	int		i;
	char	**target;
	char	**path;
	char	*str;
	char	*str2;

	i = 0;
	path = NULL;
	target = NULL;
	if (cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/')
		return (ft_absolute_path(cmd));
	path = ft_find_path(envp, path);
	if (path == NULL)
		return (NULL);
	if (ft_strchr_str (cmd, " ") != NULL)
	{
		target = ft_split (cmd, ' ');
		if (target == NULL || target[0][0] == '\0')
			return (ft_freeall (path, ft_count_path (path)), NULL);
	}
	ft_printf(1, "BITOK\n");
	while (path[i] != NULL)
	{
		ft_printf(1, "BITOK2\n");
		str = ft_strjoin(path[i], "/");
		ft_printf(1, "BITOK3\n");
		if (str == NULL)
		{
			ft_printf(1, "BITOK4\n");
			return (ft_freeall(path, ft_count_path (path)), NULL);
		}
		ft_printf(1, "BITOK5\n");
		if (target[0][0] != '\0')
		{
			ft_printf (1, "DLSBDJVADASD\n");
			str2 = ft_strjoin (str, target[0]);
		}
		ft_printf(1, "BITOK6\n");
		if (target[0][0] == '\0')
			str2 = ft_strjoin(str, cmd);
		ft_printf(1, "BITOK7\n");
		free(str);
		if (str2 == NULL)
			return (ft_freeall(path, ft_count_path (path)), NULL);
		if (ft_check_access(str2) == NULL)
			i++;
		else
			return (ft_freeall(target, ft_count_path(target)), ft_freeall(path, ft_count_path (path)), str2);
	}
	ft_printf(2, "%s: command not found\n", cmd);
	return (ft_freeall(path, ft_count_path (path)), ft_freeall(target, ft_count_path(target)), free (str2), cmd);
}*/