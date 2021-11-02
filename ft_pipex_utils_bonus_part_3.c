/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_part_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhattie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 19:15:15 by dhattie           #+#    #+#             */
/*   Updated: 2021/10/30 19:15:16 by dhattie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_free(char **new)
{
	int	i;

	i = 0;
	while (new[i])
	{
		free(new[i]);
		i++;
	}
	free(new);
	return (NULL);
}

void	ft_execve(char *argv_n, char **env)
{
	char	**paths;
	char	*true_path_command;
	char	**ar;

	if (!argv_n || !env)
		exit(4);
	ar = ft_split(argv_n, ' ');
	paths = ft_paths_parser(env);
	true_path_command = ft_check_path_command(paths, ar[0]);
	execve(true_path_command, ar, env);
	free(true_path_command);
	ft_free(ar);
	ft_free(paths);
}

void	ft_execve_pids(int argc, char **argv, char **env, int i)
{
	if (i == 0)
		ft_execve(argv[2], env);
	else if (i == argc - 4)
		ft_execve(argv[argc - 2], env);
	else
		ft_execve(argv[i + 2], env);
}

void	ft_waitpid(int argc, int *pids)
{
	int	i;

	i = -1;
	while (++i < argc - 3)
		waitpid(pids[i], NULL, 0);
	free (pids);
}
