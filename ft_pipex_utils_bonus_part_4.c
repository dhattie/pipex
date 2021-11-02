/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_part_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhattie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 19:15:15 by dhattie           #+#    #+#             */
/*   Updated: 2021/10/30 19:15:16 by dhattie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc, char **argv, char **env)
{
	if (argc < 5)
		ft_print_error("Number of arguments < 5");
	if (argc == 6 && ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])) == 0)
		second_bonus(argv, env);
}

void	temp_file(char **argv)
{
	int		temp;
	int		ret;
	char	buf[255];

	temp = open("temp_file", O_RDWR | O_CREAT, 0644);
	if (temp == -1)
		exit(EXIT_FAILURE);
	ret = 1;
	while (ret)
	{
		write(1, "> ", 2);
		ret = read(0, buf, 254);
		buf[ret] = '\0';
		if (ft_strncmp(ft_strjoin(argv[2], "\n"), buf, ft_strlen(buf)) == 0)
			break ;
		write(temp, buf, ft_strlen(buf));
	}
}

void	pipe_entrace_bonus(int *fd, char **argv, char **env)
{
	int	file_1;

	close(fd[0]);
	temp_file(argv);
	file_1 = open("temp_file", O_RDONLY, 0644);
	if (file_1 == -1)
	{
		perror("temp_file");
		exit(1);
	}
	if (dup2(file_1, 0) == -1)
		ft_print_error(strerror(errno));
	if (dup2(fd[1], 1) == -1)
		ft_print_error(strerror(errno));
	close(fd[1]);
	close(file_1);
	if (unlink("temp_file") == -1)
		ft_print_error(strerror(errno));
	ft_execve(argv[3], env);
}

void	exit_from_pipe_bonus(int *fd, char **argv, char **env)
{
	int	file_2;

	close(fd[1]);
	file_2 = open(argv[5], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file_2 == -1)
	{
		perror(argv[5]);
		exit(2);
	}
	if (dup2(fd[0], 0) == -1)
		ft_print_error(strerror(errno));
	if (dup2(file_2, 1) == -1)
		ft_print_error(strerror(errno));
	close(fd[0]);
	close(file_2);
	ft_execve(argv[4], env);
}

void	second_bonus(char **argv, char **env)
{
	int		fd[2];
	pid_t	pid1;

	if (pipe(fd) == -1)
		ft_print_error(strerror(errno));
	pid1 = fork();
	if (pid1 < 0)
		ft_print_error(strerror(errno));
	if (pid1 == 0)
		pipe_entrace_bonus(fd, argv, env);
	if (pid1 > 0)
		exit_from_pipe_bonus(fd, argv, env);
	waitpid(pid1, NULL, 0);
	close(fd[0]);
	close(fd[1]);
}
