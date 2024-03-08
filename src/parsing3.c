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

int	check_outfile(struct s_cmd *cmd, char **envp, char **argv)
{
	if (cmd->f2 == -1)
		perror(argv[4]);
	if (envp == NULL)
	{
		if (cmd->f2 >= 0)
			return (close(cmd->f2), -1);
		return (-1);
	}
	return (0);
}

static int	control_f_cmd(struct s_cmd *cmd, char *path, char *str, char *str2)
{
	str = ft_strjoin (path, "/");
	if (str == NULL)
		return (-1);
	str2 = ft_strjoin (str, cmd->first[0]);
	free(str);
	if (str2 == NULL)
		return (-1);
	if (access (str2, X_OK) == -1)
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
	if (j == 2 && cmd->f_path == NULL && cmd->first != NULL && path != NULL)
		if (control_f_cmd(cmd, path, str, str2) == -1)
			return (-1);
	if (j == 3 && cmd->s_path == NULL && cmd->second != NULL && path != NULL)
	{
		str = ft_strjoin(path, "/");
		if (str == NULL)
			return (-1);
		if (cmd->second[0] != NULL)
			str2 = ft_strjoin(str, cmd->second[0]);
		if (str2 == NULL)
			return (free (str), -1);
		if (access(str2, X_OK) == -1)
			return (free(str), free(str2), 1);
		cmd->s_path = ft_strjoin(cmd->s_path, str2);
		free (str2);
		if (cmd->s_path == NULL)
			return (free (str), -1);
	}
	return (free (str), 0);
}

void	ft_initialize(char **cmd_path, char *argv)
{
	if (ft_strchr(argv, ' '))
		*cmd_path = ft_strjoin_space(*cmd_path, argv);
	else
		*cmd_path = ft_strjoin(*cmd_path, argv);
}
