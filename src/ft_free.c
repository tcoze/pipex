/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:53:45 by tcoze             #+#    #+#             */
/*   Updated: 2024/02/28 08:53:45 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	double_close(int f1, int f2)
{
	if (f1 >= 0)
		if (close(f1) == -1)
			return (-1);
	if (f2 >= 0)
		if (close(f2) == -1)
			return (-1);
	return (0);
}

void	clear_struct(struct s_cmd *cmd)
{
	if (cmd->f_path != NULL)
		free(cmd->f_path);
	if (cmd->s_path != NULL)
		free(cmd->s_path);
	if (cmd->first != NULL)
	{
		if (ft_count_path (cmd->first) != -1)
			ft_freeall (cmd->first, ft_count_path (cmd->first));
		else
			free(cmd->first);
	}
	if (cmd->second != NULL)
	{
		if (ft_count_path (cmd->second) != -1)
			ft_freeall (cmd->second, ft_count_path (cmd->second));
		else
			free(cmd->second);
	}
}

void	ft_freeall(char **out, int j)
{
	if (out != NULL)
	{
		while (j > -1)
		{
			if (out[j])
				free (out[j]);
			j--;
		}
		if (out)
			free (out);
	}
}

int	ft_count_path(char **path)
{
	int	i;

	i = 0;
	if (path == NULL)
		return (-1);
	while (path[i] && path[i + 1])
		i++;
	return (i);
}
