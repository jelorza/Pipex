/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:27:42 by jelorza-          #+#    #+#             */
/*   Updated: 2022/04/14 19:13:04 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_acces(t_pipe_args *data, t_pipe_routes *routes)
{
	int	i;
	int	j;

	routes->x1 = -1;
	routes->x2 = -1;
	i = 0;
	while (routes->path_routes_cmd1[i])
	{
		j = access(routes->path_routes_cmd1[i], F_OK);
		if (j == 0)
			routes->x1 = i;
		j = access(routes->path_routes_cmd2[i], F_OK);
		if (j == 0)
			routes->x2 = i;
		i++;
	}
	if (routes->x1 == -1 || routes->x2 == -1)
	{
		write (1, "Command not found\n", 17);
		ft_free(data, routes);
		exit(0);
	}
}

void	ft_process_pipe(t_pipe_args *data, t_pipe_routes *routes, char **env)
{
	t_pipe_fds	fds;
	int			pid1;	
	int			pid2;
	int			status;

	fds.fd_infile = open(data->infile, O_RDONLY);
	if (fds.fd_infile == -1)
		perror("zsh");
	fds.fd_outfile = open(data->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	pipe(fds.fd1);
	pid1 = ft_fork1(routes, &fds, env, data);
	close(fds.fd1[1]);
	waitpid(pid1, &status, 0);
	pid2 = ft_fork2(routes, &fds, env, data);
	close (fds.fd1[0]);
	waitpid(pid2, &status, 0);
}

int	ft_fork1(t_pipe_routes *routes, t_pipe_fds *fds,
	char **env, t_pipe_args *data)
{
	int	pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		if (fds->fd_infile == -1)
			exit(1);
		close (fds->fd1[0]);
		dup2 (fds->fd_infile, STDIN_FILENO);
		dup2 (fds->fd1[1], STDOUT_FILENO);
		close (fds->fd1[1]);
		close (fds->fd_infile);
		execve (routes->path_routes_cmd1[routes->x1], data->cmd1_split, env);
		exit(0);
	}
	return (pid1);
}

int	ft_fork2(t_pipe_routes *routes, t_pipe_fds *fds,
	char **env, t_pipe_args *data)
{
	int	pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		dup2 (fds->fd1[0], STDIN_FILENO);
		dup2 (fds->fd_outfile, STDOUT_FILENO);
		close (fds->fd1[0]);
		close (fds->fd_outfile);
		execve (routes->path_routes_cmd2[routes->x2],
			data->cmd2_split, env);
		exit(0);
	}
	return (pid2);
}
