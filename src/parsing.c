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

static void	print_not_found(struct s_cmd *cmd, int j)
{
	if (j == 2 && cmd->f_path == NULL && cmd->f1 != -1)
	{
		if (cmd->first != NULL)
			ft_printf (2, "%s: command not found\n", cmd->first[0]);
		else
			ft_printf (2, """: command not found\n");
	}
	if (j == 3 && cmd->s_path == NULL && cmd->f2 != -1)
	{
		if (cmd->second != NULL)
			ft_printf (2, "%s: command not found\n", cmd->second[0]);
		else
			ft_printf (2, """: command not found\n");
	}
}

int	fill_path(struct s_cmd *cmd, char **path, int j)
{
	int	i;
	int	control_value;

	i = 0;
	while (path[i])
	{
		control_value = control_path(cmd, path[i], j);
		if (control_value == -1)
			return (clear_struct(cmd), ft_freeall(path, ft_count_path(path)),
				-1);
		i++;
	}
	print_not_found(cmd, j);
	return (0);
}

int	fill_struct(char *argv, struct s_cmd *cmd, char **path, int j)
{
	if (j == 2)
	{
		if (argv[0] != '\0')
		{
			cmd->first = ft_split (argv, ' ');
			if (cmd->first[0] == NULL)
				return (ft_freeall (path, ft_count_path (path)), -1);
		}
	}
	if (j == 3)
	{
		if (argv[0] != '\0')
		{
			cmd->second = ft_split (argv, ' ');
			if (cmd->second == NULL)
				return (ft_freeall (path, ft_count_path (path)), -1);
		}
	}
	return (0);
}

int	parsing(char **argv, char **envp, struct s_cmd *cmd)
{
	char	**path;
	char	temp;
	int		i;

	i = 1;
	path = NULL;
	path = ft_find_path (envp, path);
	while (++i <= 3)
	{
		if (i == 2)
			temp = check_absolute_path(argv[i], &cmd->first, &cmd->f_path);
		if (i == 3)
			temp = check_absolute_path(argv[i], &cmd->second, &cmd->s_path);
		if (temp == -1)
			return (ft_freeall(path, ft_count_path(path)), -1);
		if (temp == 0 && path != NULL)
			if (ft_check_cmd(argv[i], cmd, path, i) == -1)
				return (-1);
		if (temp == 0 && path == NULL)
			ft_printf(2, "%s: command not found\n", argv[i]);
	}
	return (ft_freeall(path, ft_count_path(path)), 0);
}
