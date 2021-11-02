/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_part_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhattie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 19:14:56 by dhattie           #+#    #+#             */
/*   Updated: 2021/10/30 19:14:58 by dhattie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	middle_pipes(int **pipes, int i, int argc)
{
	if (dup2(pipes[i - 1][0], 0) == -1)
		ft_print_error(strerror(errno));
	if (dup2(pipes[i][1], 1) == -1)
		ft_print_error(strerror(errno));
	ft_close_pipes(pipes, argc);
}

void	last_pipes(int **pipes, char **argv, int argc)
{
	int	outfile;

	outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror(argv[argc - 1]);
		exit(2);
	}
	if (dup2(pipes[argc - 5][0], 0) == -1)
		ft_print_error(strerror(errno));
	if (dup2(outfile, 1) == -1)
		ft_print_error(strerror(errno));
	close(outfile);
	ft_close_pipes(pipes, argc);
}

void	ft_select_pipes(int argc, char **argv, int **pipes, int i)
{
	if (i == 0)
		first_pipes(pipes, argv, argc);
	else if (i == argc - 4)
		last_pipes(pipes, argv, argc);
	else
		middle_pipes(pipes, i, argc);
}

char	**ft_paths_parser(char **env)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (paths);
}

char	*ft_check_path_command(char **path, char *argv)
{
	int		i;
	char	*true_path_command;
	char	*str;

	if (!path || !argv)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		str = ft_strjoin(path[i], "/");
		true_path_command = ft_strjoin(str, argv);
		if (access(true_path_command, 1) == 0)
			break ;
	}
	return (true_path_command);
}
