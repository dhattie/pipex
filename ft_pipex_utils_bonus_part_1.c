/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_part_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhattie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 19:15:15 by dhattie           #+#    #+#             */
/*   Updated: 2021/10/30 19:15:16 by dhattie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*ft_create_pids(int argc)
{
	int	*pids;

	pids = malloc((argc - 3) * sizeof (int));
	if (!pids)
		exit (2);
	return (pids);
}

void	ft_print_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

int	**ft_create_pipes(int argc)
{
	int	**pipes;
	int	i;

	pipes = malloc((argc - 4) * sizeof(int *));
	if (!pipes)
		exit(1);
	i = -1;
	while (++i < argc - 4)
	{
		pipes[i] = malloc(2 * sizeof (int));
		if (!pipes[i])
			exit(1);
		if (pipe(pipes[i]) == -1)
			ft_print_error(strerror(errno));
	}
	return (pipes);
}

void	ft_close_pipes(int **pipes, int argc)
{
	int	j;

	j = 0;
	while (j < argc - 4)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	first_pipes(int **pipes, char **argv, int argc)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0644);
	if (infile == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	if (dup2(infile, 0) == -1)
		ft_print_error(strerror(errno));
	if (dup2(pipes[0][1], 1) == -1)
		ft_print_error(strerror(errno));
	close(infile);
	ft_close_pipes(pipes, argc);
}
