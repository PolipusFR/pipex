/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:26:31 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/19 17:23:11 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_c_and_e(char **tab_cmd, char *path_line, char *input_cmd)
{
	int	i;

	i = 0;
	free(path_line);
	free(input_cmd);
	while (tab_cmd[i])
		free(tab_cmd[i++]);
	free(tab_cmd);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i++]);
	}
	free(tab);
}

void	free_all_tabs(char **tab1, char **tab2)
{
	free_tab(tab1);
	free_tab(tab2);
}

void	check_and_execute(char *cmd, char **envp, int pid)
{
	char	**tab_cmd;
	char	*path_line;
	char	*input_cmd;

	path_line = get_path_line(envp);
	input_cmd = get_path(cmd, path_line);
	tab_cmd = ft_split(cmd, ' ');
	if (execve(input_cmd, tab_cmd, envp) == -1)
	{
		free_c_and_e(tab_cmd, path_line, input_cmd);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		if (pid == 1)
			exit (127);
		else
			exit (10);
	}
	else
		free_c_and_e(tab_cmd, path_line, input_cmd);
}
