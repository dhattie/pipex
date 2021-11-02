/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhattie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:23:41 by dhattie           #+#    #+#             */
/*   Updated: 2021/11/02 20:23:49 by dhattie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/fcntl.h>
# include "libft.h"

int		*ft_create_pids(int argc);
void	ft_print_error(char *str);
int		**ft_create_pipes(int argc);
void	ft_close_pipes(int **pipes, int argc);
void	first_pipes(int **pipes, char **argv, int argc);
void	middle_pipes(int **pipes, int i, int argc);
void	last_pipes(int **pipes, char **argv, int argc);
void	ft_select_pipes(int argc, char **argv, int **pipes, int i);
char	**ft_paths_parser(char **env);
char	*ft_check_path_command(char **path, char *argv);
void	*ft_free(char **new);
void	ft_execve(char *argv_n, char **env);
void	ft_execve_pids(int argc, char **argv, char **env, int i);
void	ft_waitpid(int argc, int *pids);
void	check_args(int argc, char **argv, char **envp);
void	pipe_entrace_bonus(int *fd, char **argv, char **env);
void	exit_from_pipe_bonus(int *fd, char **argv, char **env);
void	second_bonus(char **argv, char **env);
void	pipe_entrace(int *fd, char **argv, char **env);
void	exit_from_pipe(int *fd, char **argv, char **env);

#endif