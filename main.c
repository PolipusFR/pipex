/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:32:43 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/19 17:56:54 by lsabatie         ###   ########.fr       */
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
	if (envp[0] == NULL)
		return (ft_strdup("\0"));
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
				envp[i][2] == 'T' && envp[i][3] == 'H')
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

char	*get_path(char *input_cmd, char	*path_line)
{
	char	**path_tab;
	char	*cmd;
	char	**cmd_no_args;
	char	*tmp;
	int		i;

	i = 0;
	path_tab = ft_split(path_line, ':');
	cmd_no_args = ft_split(input_cmd, ' ');
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		free(path_tab[i]);
		path_tab[i] = tmp;
		cmd = ft_strjoin(path_tab[i++], cmd_no_args[0]);
		if ((access(cmd, F_OK | X_OK)) == 0)
		{
			free_all_tabs(cmd_no_args, path_tab);
			return (cmd);
		}
		free(cmd);
	}
	free_all_tabs(cmd_no_args, path_tab);
	return (ft_strdup(input_cmd));
}

void	parent_process(char **av, int *pipefd, char **envp)
{
	int	fd;

	close(pipefd[1]);
	fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd < 0)
	{
		close(pipefd[0]);
		perror(av[4]);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	waitpid(0, NULL, WNOHANG);
	check_and_execute(av[3], envp, 1);
}

void	child_process(char **av, int *pipefd, char **envp)
{
	int		fd;

	close(pipefd[0]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		close(pipefd[1]);
		ft_putstr_fd("pipex: ", 2);
		perror(av[1]);
		exit (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	check_and_execute(av[2], envp, 0);
}

int	main(int ac, char **av, char **envp)
{
	int	pipefd[2];
	int	pid;

	if (ac != 5)
	{
		ft_putstr_fd("pipex: syntax : \"./pipex file1 cmd1 cmd2 file2\"\n", 2);
		return (1);
	}
	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (!pid)
		child_process(av, pipefd, envp);
	parent_process(av, pipefd, envp);
}
