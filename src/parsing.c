/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:00:38 by tcoze             #+#    #+#             */
/*   Updated: 2024/03/02 12:14:46 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

int control_path(struct s_cmd *cmd, char *path, int j)
{
	char	*str;
	char	*str2;

	if (j == 2 && cmd->f_path == NULL && cmd->first != NULL)
	{
		str = ft_strjoin (path, "/");
		if (str == NULL)
			return (-1);
		str2 = ft_strjoin (str, cmd->first[0]);
		free (str);
		if (str2 == NULL)
			return (-1);
		if (access (str2, F_OK) == -1)
			return (free (str2), 1);
		cmd->f_path = ft_strjoin (cmd->f_path, str2);
		free (str2);
		if (cmd->f_path == NULL)
			return (-1);
	}
	if (j == 3 && cmd->s_path == NULL && cmd->second != NULL)
	{
		str = ft_strjoin (path, "/");
		if (str == NULL)
		return (-1);
		str2 = ft_strjoin (str, cmd->second[0]);
		free (str);
		if (str2 == NULL)
			return (-1);
		if (access (str2, F_OK) == -1)
			return (free (str2), 1);
		cmd->s_path = ft_strjoin (cmd->s_path, str2);
		free (str2);
		if (cmd->s_path == NULL)
			return (-1);
	}
	return (0);
}

int fill_path(struct s_cmd *cmd, char **path, int j)
{
	int i;
	int control_value;

	i = 0;
	while(path[i])
	{
		control_value = control_path(cmd, path[i], j);
		if (control_value == -1)
			return (clear_struct(cmd), -1);
		i++;
	}
	if (j == 2 && cmd->f_path == NULL)
	{
		if (cmd->first != NULL)
			ft_printf (2, "%s: command not found\n", cmd->first[0]);
		else
			ft_printf (2, """: command not found\n");
	}
	if (j == 3 && cmd->s_path == NULL)
	{
		if (cmd->second != NULL)
			ft_printf (2, "%s: command not found\n", cmd->second[0]);
		else
			ft_printf (2, """: command not found\n");
	}
	return (0);
}

int	fill_struct(char *argv, struct s_cmd *cmd, char **path, int j)
{
	if (j == 2) // REMPLISSAGE STRUCT PREMIERE COMMANDE
	{
		if (argv[0] != '\0')
		{
			cmd->first = ft_split (argv, ' ');
			if (cmd->first[0] == NULL)
				return (ft_freeall (path, ft_count_path (path)), -1);
			if (ft_strncmp(cmd->first[0], "sudo", 4) == 0)
			{
				ft_printf (2, "/usr/bin/sudo: Permission denied\n");
				ft_freeall (cmd->first, ft_count_path (cmd->first));
			}
		}
	}
	if (j == 3) // REMPLISSAGE STRUCT SECONDE COMMANDE
	{
		if (argv[0] != '\0')
		{
			cmd->second = ft_split (argv, ' ');
			if (cmd->second == NULL)
				return (ft_freeall (path, ft_count_path (path)), clear_struct (
					cmd), -1);
			if (ft_strncmp(cmd->second[0], "sudo", 4) == 0)
			{
				ft_printf (2, "/usr/bin/sudo: Permission denied\n");
				ft_freeall (cmd->second, ft_count_path (cmd->second));
			}
		}
	}
	return (0);
}

int	parsing(char **argv, char **envp, struct s_cmd *cmd)
{
	char **path;
	char temp;
	int i;

	i = 2;
	path = NULL;
	path = ft_find_path (envp, path);
	if (path == NULL)
		return (-1);
	while (i <= 3)
	{
		if (i == 2)
			temp = check_absolute_path(argv[i], cmd->first, cmd->f_path);
		if (i == 3)
			temp = check_absolute_path(argv[i], cmd->second, cmd->s_path);
		if (temp == -1)
			return (-1);
		if (temp == 0)
			if (ft_check_cmd(argv[i], cmd, path, i) == -1)
				return (-1);
		i++;
	}
	ft_freeall(path, ft_count_path(path));
	return (0);
}
