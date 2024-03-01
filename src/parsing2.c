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

static char	*ft_absolute_path(char	*cmd)
{
	if (access(cmd, F_OK) == -1)
		return (NULL);
	return (cmd);
}

char	*ft_check_access(char *str2)
{
	if (access (str2, F_OK) == -1)
		return (free(str2), NULL);
	else
		return (str2);
}

char	*ft_check_cmd(char *cmd, char **envp)
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
}