/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:49:28 by alegrix           #+#    #+#             */
/*   Updated: 2025/02/05 01:45:03 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

char	*find_path(char *cmop, char **envp)
{
	int		i;
	char	**paths;
	char	*fpath;
	char	*temp;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		fpath = ft_strjoin(temp, cmop);
		free(temp);
		if (access(fpath, X_OK) == 0)
			return (free_array(paths), fpath);
		free(fpath);
		i++;
	}
	return (free_array(paths), NULL);
}

void	execu(char **envp, char **cmop)
{
	char	*path;

	path = find_path(cmop[0], envp);
	if (path == NULL)
	{
		free_array(cmop);
		perror("Impossible Path");
		exit(3);
	}
	execve(path, cmop, envp);
	perror("Invailible commande");
	free_array(cmop);
	free(path);
	exit(8);
}

void	children(int fd[2], char **argv, char **envp)
{
	int		feelin;
	char	**cmop;

	close(fd[0]);
	feelin = open(argv[1], O_RDONLY, 0777);
	if (feelin == -1)
	{
		perror("File1 not found");
		exit(2);
	}
	cmop = ft_split(argv[2], ' ');
	dup2(fd[1], STDOUT_FILENO);
	dup2(feelin, STDIN_FILENO);
	close(fd[1]);
	close(feelin);
	access_path(envp, cmop, argv);
	execu(envp, cmop);
}

void	parent(int fd[2], char **argv, char **envp)
{
	int		feelout;
	char	**cmop;

	close(fd[1]);
	feelout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (feelout == -1)
		exit(2);
	cmop = ft_split(argv[3], ' ');
	dup2(fd[0], STDIN_FILENO);
	dup2(feelout, STDOUT_FILENO);
	close(fd[0]);
	close(feelout);
	access_path(envp, cmop, argv);
	execu(envp, cmop);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit(4);
		pid1 = fork();
		if (pid1 == 0)
			children(fd, argv, envp);
		pid2 = fork();
		if (pid1 == -1 || pid2 == -1)
			exit(1);
		if (pid2 == 0)
			parent(fd, argv, envp);
		close(fd[0]);
		close(fd[1]);
		return (waitpid(pid1, NULL, 0), waitpid(pid2, NULL, 0), 0);
	}
	else
	{
		ft_printf("Bad arguments, try this :\n");
		ft_printf("./pipex file1 cmd1 cm2 file2\n");
	}
}
