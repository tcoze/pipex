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

static int	fill_struct(struct s_cmd cmd, char **path, int j)
{
	if (j == 2) // REMPLISSAGE STRUCT PREMIERE COMMANDE
	{
		cmd.first = ft_split(cmd, ' ');
		if (cmd.first == NULL)
			return (ft_freeall (path, ft_count_path(path)), -1);
		if (ft_strncmp (cmd.first[0], "sudo", 4))
		{
			ft_printf (2, "/usr/bin/sudo: Permission denied\n");
			ft_freeall (cmd.first, ft_count_path (cmd.first));
		}
	}
	if (j == 3) // REMPLISSAGE STRUCT SECONDE COMMANDE
	{
		cmd.second = ft_split(cmd, ' ');
		if (cmd.second == NULL)
			return (ft_freeall(path, ft_count_path(path)), clear_struct(cmd), -1);
		if (ft_strncmp (cmd.second[0], "sudo", 4))
		{
			ft_printf (2, "/usr/bin/sudo: Permission denied\n");
			ft_freeall (cmd.second, ft_count_path (cmd.second));
		}
	}
	return (0);
}

char	*ft_check_cmd(char *argv, struct s_cmd cmd, char **path, int j)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	if (fill_struct(cmd, path, j) == -1) // STRUCT FILL ICI, PATH A CONTROLLER
		return (-1);


}

}

int	parsing(char **argv, char **envp, struct s_cmd cmd)
{
	char **path;
	char temp;
	int i;

	i = 1;
	path = ft_find_path (envp, path);
	if (path == NULL)
		return (-1);
	while (i < 3)
	{
		if (i == 1)
			temp = check_absolute_path (argv[i], cmd.first, cmd.f_path);
		if (i == 2)
			temp = check_absolute_path (argv[i], cmd.second, cmd.s_path);
		if (temp == -1)
			return (-1);
		if (temp == 0)
		{
		}
	i++;
	}
	return (0);
}



	/*
			test = ft_check_cmd (argv[2], envp);
		if (test == NULL)
			ft_printf (2, "%s: command not found\n", argv[2]);
		free (test);
	}
	if (argv[3][0] != '\0')
	{
		test = ft_check_cmd (argv[3], envp);
		if (test == NULL)
			ft_printf (2, "%s: command not found\n", argv[3]);
	}
	if (test != NULL)
		free(test);
	return (0);

	if (ft_strncmp(argv[2], "sudo", 4) == 0
		|| ft_strncmp(argv[3], "sudo", 4) == 0)
		ft_printf(2, "/usr/bin/sudo: Permission denied\n");
}*/