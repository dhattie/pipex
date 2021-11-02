/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhattie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:58:09 by dhattie           #+#    #+#             */
/*   Updated: 2021/10/30 11:58:14 by dhattie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	*pids;
	int	**pipes;
	int	i;

	check_args(argc, argv, env);
	pids = ft_create_pids(argc);
	pipes = ft_create_pipes(argc);
	i = -1;
	while (++i < argc - 3)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			ft_print_error(strerror(errno));
		if (pids[i] == 0)
		{
			ft_select_pipes(argc, argv, pipes, i);
			ft_execve_pids(argc, argv, env, i);
		}
	}
	ft_close_pipes(pipes, argc);
	ft_waitpid(argc, pids);
}
