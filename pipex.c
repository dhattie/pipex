/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhattie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:36:09 by dhattie           #+#    #+#             */
/*   Updated: 2021/08/12 19:36:11 by dhattie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_entrace(int *fd, char **argv, char **env)
{
	int	file_1;

	close(fd[0]);
	file_1 = open(argv[1], O_RDONLY, 0644);
	if (file_1 == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	if (dup2(file_1, 0) == -1)
		ft_print_error(strerror(errno));
	if (dup2(fd[1], 1) == -1)
		ft_print_error(strerror(errno));
	close(fd[1]);
	close(file_1);
	ft_execve(argv[2], env);
}

void	exit_from_pipe(int *fd, char **argv, char **env)
{
	int	file_2;

	close(fd[1]);
	file_2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_2 == -1)
	{
		perror(argv[4]);
		exit(2);
	}
	if (dup2(fd[0], 0) == -1)
		ft_print_error(strerror(errno));
	if (dup2(file_2, 1) == -1)
		ft_print_error(strerror(errno));
	close(fd[0]);
	close(file_2);
	ft_execve(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid1;

	if (argc != 5)
		ft_print_error("Number of arguments is not equal to 5 \n");
	if (pipe(fd) == -1)
		ft_print_error(strerror(errno));
	pid1 = fork();
	if (pid1 < 0)
		ft_print_error(strerror(errno));
	if (pid1 == 0)
		pipe_entrace(fd, argv, env);
	if (pid1 > 0)
		exit_from_pipe(fd, argv, env);
	waitpid(pid1, NULL, 0);
	close(fd[0]);
	close(fd[1]);
}
