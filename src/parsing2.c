/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:46:07 by tcoze             #+#    #+#             */
/*   Updated: 2024/03/06 16:20:20 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

int	ft_check_cmd(char *argv, struct s_cmd *cmd, char **path, int j)
{
	if (fill_struct(argv, cmd, path, j) == -1)
		return (-1);
	if (fill_path(cmd, path, j) == -1)
		return (-1);
	return (0);
}

char	*ft_check_access(char *str2)
{
	if (access (str2, F_OK) == -1)
		return (NULL);
	else
		return (str2);
}

int	check_absolute_path(char *argv, char ***cmd, char **cmd_path)
{
	int		i;
	char	**temp;

	i = 0;
	temp = NULL;
	if (ft_strchr_str (argv, "/"))
	{
		cmd_path[0] = ft_strjoin_space(cmd_path[0], argv);
		temp = ft_split(argv, '/');
		if (cmd_path == NULL || temp == NULL)
			return (-1);
		while (temp[i] && temp[i + 1])
			i++;
		cmd[0] = ft_split(temp[i], ' ');
		if (cmd == NULL)
			return (-1);
		if (ft_check_access(cmd_path[0]) == NULL)
		{
			ft_printf (2, "%s: command not found\n", cmd[0][0]);
			return (free(cmd_path), ft_freeall(cmd[0], ft_count_path(cmd[0])),
				ft_freeall(temp, ft_count_path(temp)), -1);
		}
		return (ft_freeall(temp, ft_count_path(temp)), 1);
	}
	return (0);
}

char	**ft_find_path(char **envp, char **path)
{
	int		i;
	char	*p_find;

	i = 0;
	if (envp == NULL)
		return (NULL);
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
	return (NULL);
}
