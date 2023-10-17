/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:32:43 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/17 19:30:41 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_line(char **envp)
{
	int		i;
	int		j;
	char	*path_line;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			while (envp[i][j] && envp[i][j + 5])
			{
				envp[i][j] = envp[i][j + 5];
				j++;
			}
			envp[i][j] = '\0';
			path_line = ft_strdup(envp[i]);
		}
		i++;
	}
	return (path_line);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	printf("----------------------------FREE_TAB-------------------------\n");
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		free(tab[i++]);
	}
	free(tab);
}

char	*get_path(char *input_cmd, char	*path_line)
{
	char	**path_tab;
	char	*cmd;
	char	**cmd_no_args;
	int		i;

	i = 0;
	path_tab = ft_split(path_line, ':');
	cmd_no_args = ft_split(input_cmd, ' ');
	while (path_tab[i])
	{
		path_tab[i] = ft_strjoin(path_tab[i], "/");
		printf("%s\n", path_tab[i]);
		cmd = ft_strjoin(path_tab[i], cmd_no_args[0]);
		if ((access(cmd, F_OK | X_OK)) == 0)
		{
			free_tab(cmd_no_args);
			free_tab(path_tab);
			return (cmd);
		}
		i++;
	}
	free(cmd);
	free_tab(cmd_no_args);
	free_tab(path_tab);
	return input_cmd;
}

void	check_and_execute(char *cmd, char **envp)
{
	char	**tab_cmd;
	char	*path_line;
	char	*input_cmd;
	int		i;
	
	i = 0;
	path_line = get_path_line(envp);
	input_cmd = get_path(cmd, path_line);
	tab_cmd = ft_split(cmd, ' ');
	if (execve(input_cmd, tab_cmd, envp) == -1)
	{
		printf("command not found");
		free(path_line);
		free(input_cmd);
		while (tab_cmd[i])
			free(tab_cmd[i++]);
		free(tab_cmd);
		exit (1);
	}
	else
	{
		free(path_line);
		free(input_cmd);
		while (tab_cmd[i])
			free(tab_cmd[i++]);
		free(tab_cmd);
	}
}

void	parent_process(char **av, int *pipefd, char **envp)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd < 0)
		exit (1);
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
	check_and_execute(av[3], envp);
}

void	child_process(char **av, int *pipefd, char **envp)
{
	int		fd;

	fd = open(av[1], O_RDONLY, 0644);
	if (fd < 0)
		exit (1);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
	check_and_execute(av[2], envp);
}

int	main(int ac, char **av, char **envp)
{
	int	pipefd[2];
	int	pid;
	char *arg[1] = {" "};

	execve("env", arg, envp);
	if (ac != 5)
	{
		return 1;
	}
	if (pipe(pipefd) == -1)
		return 1;
	pid = fork();
	if (pid < 0)
		return 1;
	if (!pid)
		child_process(av, pipefd, envp);
	parent_process(av, pipefd, envp);
}