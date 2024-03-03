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

int	ft_check_cmd(char *argv, struct s_cmd *cmd, char **path, int j)
{
	if (fill_struct(argv, cmd, path, j) == -1) // STRUCT FILL ICI, PATH A CONTROLLER
		return (-1);
	if (fill_path(cmd, path, j) == -1) // PATH FILL ICI
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

int	check_absolute_path(char *argv, char **cmd, char *cmd_path)
{
	int		i;
	char	**temp;

	i = 0;
	temp = NULL;
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