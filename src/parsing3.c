/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:45:35 by tcoze             #+#    #+#             */
/*   Updated: 2024/03/05 16:45:35 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

static int	control_f_cmd(struct s_cmd *cmd, char *path, char *str, char *str2)
{
	str = ft_strjoin (path, "/");
	if (str == NULL)
		return (-1);
	str2 = ft_strjoin (str, cmd->first[0]);
	free(str);
	if (str2 == NULL)
		return (-1);
	if (access (str2, F_OK) == -1)
		return (free(str2), 1);
	cmd->f_path = ft_strjoin (cmd->f_path, str2);
	free (str2);
	if (cmd->f_path == NULL)
		return (-1);
	return (0);
}

int	control_path(struct s_cmd *cmd, char *path, int j)
{
	char	*str;
	char	*str2;

	str = NULL;
	str2 = NULL;
	if (j == 2 && cmd->f_path == NULL && cmd->first != NULL)
		if (control_f_cmd(cmd, path, str, str2) == -1)
			return (-1);
	if (j == 3 && cmd->s_path == NULL && cmd->second != NULL)
	{
		str = ft_strjoin(path, "/");
		if (str == NULL)
			return (-1);
		str2 = ft_strjoin(str, cmd->second[0]);
		free (str);
		if (str2 == NULL)
			return (-1);
		if (access (str2, F_OK) == -1)
			return (free (str2), 1);
		cmd->s_path = ft_strjoin(cmd->s_path, str2);
		free (str2);
		if (cmd->s_path == NULL)
			return (-1);
	}
	return (0);
}
