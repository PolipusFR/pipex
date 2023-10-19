/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:33:29 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/19 13:32:01 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h> // malloc et free
# include <stdio.h> // printf
# include <fcntl.h> // open

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		get_string_size(char *buf);
char	*fill_string(int fd, char *buf);
int		check_newline(char *buf);
char	*gnl_strjoin(char *s1, char *s2);
void	buffer_reset(char *buf);
int		gnl_strlen(const char *s);
int		gnl_strlen_buff(char *str);
char	*gnl_strdup(const char *s1);
char	*get_next_line(int fd);

char	*ft_strdup(const char *s1);

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);

void	free_c_and_e(char **tab_cmd, char *path_line, char *input_cmd);
void	free_tab(char **tab);
void	free_all_tabs(char **tab1, char **tab2);
void	check_and_execute(char *cmd, char **envp);

char	*get_path(char *input_cmd, char	*path_line);
char	*get_path_line(char **envp);

#endif