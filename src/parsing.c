/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:00:38 by tcoze             #+#    #+#             */
/*   Updated: 2024/02/27 11:14:06 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

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

/*int	check_parsing(char *argv[], char **envp)
{
	char	*test;

	test = NULL;
	if (ft_strncmp(argv[2], "sudo", 4) == 0
		|| ft_strncmp(argv[3], "sudo", 4) == 0)
		ft_printf(2, "/usr/bin/sudo: Permission denied\n");
	if (argv[2][0] != '\0')
	{
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
}*/
