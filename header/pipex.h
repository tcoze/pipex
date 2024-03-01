/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoze <tcoze@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:59:42 by tcoze             #+#    #+#             */
/*   Updated: 2024/02/28 08:59:44 by tcoze            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_cmd
{
	char	**first;
	char	**second;
	char	*f_path;
	char	*s_path;
}	t_cmd;

int		check_parsing(char *argv[], char **envp);
char	**ft_split(char *s, char c);
char	*ft_strchr_str(char *s, char *c);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_check_cmd(char *cmd, char **envp);
int		child_process(int f1, struct s_cmd cmd, char **envp, int *pfd);
int		parent_process(int f2, struct s_cmd cmd, char **envp, int *pfd);
int		pipex(int f1, struct s_cmd cmd, char **envp, int f2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_count_path(char **path);
char	*ft_check_access(char *str2);
char	**ft_find_path(char **envp, char **path);
void	clear_struct_f(struct s_cmd cmd);
void	clear_struct(struct s_cmd cmd);
void	ft_freeall(char **out, int j);

#endif
