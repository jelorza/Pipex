/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:03:22 by jelorza-          #+#    #+#             */
/*   Updated: 2022/04/10 20:29:36 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipe_args		data;
	t_pipe_routes	routes;

	if (argc != 5)
	{
		write (1, "error de argumentos amigo", 25);
		exit (0);
	}
	else
	{
		ft_clean_args(argv, &data);
		ft_path_routes(env, &routes, &data);
		ft_acces(&data, &routes);
		ft_process_pipe(&data, &routes, env);
		ft_free(&data, &routes);
	}
	return (0);
}

void	ft_process_pipe(t_pipe_args *data, t_pipe_routes *routes, char **env)
{
	t_pipe_fds	fds;
	int			pid1;	
	int			pid2;
	int			status;

	fds.fd_infile = open(data->infile, O_RDONLY);
	fds.fd_outfile = open(data->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	pipe(fds.fd1);
	pid1 = fork();
	if (pid1 == 0)
	{
		close (fds.fd1[0]);
		dup2 (fds.fd_infile, STDIN_FILENO);
		dup2 (fds.fd1[1], STDOUT_FILENO);
		close (fds.fd1[1]);
		close (fds.fd_infile);
		execve (routes->path_routes_cmd1[routes->x1], data->cmd1_split, env);
		exit(0);
	}
	else
	{
		close(fds.fd1[1]);
		waitpid(pid1, &status, 0);
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2 (fds.fd1[0], STDIN_FILENO);
			dup2 (fds.fd_outfile, STDOUT_FILENO);
			close (fds.fd1[0]);
			close (fds.fd_outfile);
			execve (routes->path_routes_cmd2[routes->x2],
				data->cmd2_split, env);
			exit(0);
		}
		else
		{
			close (fds.fd1[0]);
			waitpid(pid2, &status, 0);
		}
	}
}

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
	printf("x1 = %d, x2 = %d\n", routes->x1, routes->x2);
	if (routes->x1 == -1 || routes->x2 == -1)
	{
		write (1, "Comando no existe amigo\n", 24);
		ft_free(data, routes);
		exit(0);
	}
}

void	ft_clean_args(char **argv, t_pipe_args *data)
{
	data->infile = argv[1];
	data->outfile = argv[4];
	data->cmd1_split = ft_split(argv[2], ' ');
	data->cmd1_str_cant = ft_substr_counter(argv[2], ' ');
	data->cmd2_split = ft_split(argv[3], ' ');
	data->cmd2_str_cant = ft_substr_counter(argv[3], ' ');
}

void	ft_path_routes(char **env, t_pipe_routes *routes, t_pipe_args *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 1)
			ft_proces_path(env[i], routes, data);
		i++;
	}
}

int	ft_proces_path(char *env, t_pipe_routes *routes, t_pipe_args *data)
{
	int		i;
	char	**temp1;
	char	**temp2;

	routes->path_routes_cant = ft_substr_counter(env, ':');
	env = ft_substr(env, 5, ft_strlen(env));
	temp1 = ft_split(env, ':');
	free(env);
	temp2 = malloc (sizeof(char **) * routes->path_routes_cant + 1);
	routes->path_routes_cmd1 = malloc (sizeof(char **)
			* routes->path_routes_cant + 1);
	routes->path_routes_cmd2 = malloc (sizeof(char **)
			* routes->path_routes_cant + 1);
	if (!temp2 || !routes->path_routes_cmd1 || !routes->path_routes_cmd2)
		return (00);
	i = -1;
	while (++i < routes->path_routes_cant)
	{
		temp2[i] = ft_join(temp1[i], "/");
		free(temp1[i]);
	}
	temp2[i] = 00;
	free(temp1);
	i = -1;
	while (++i < routes->path_routes_cant)
	{
		routes->path_routes_cmd1[i] = ft_join(temp2[i], data->cmd1_split[0]);
		routes->path_routes_cmd2[i] = ft_join(temp2[i], data->cmd2_split[0]);
		free(temp2[i]);
	}
	routes->path_routes_cmd1[i] = 00;
	routes->path_routes_cmd2[i] = 00;
	free(temp2);
	i = -1;
	return (0);
}

void	ft_free(t_pipe_args *args, t_pipe_routes *routes)
{
	int	i;

	i = -1;
	if (args->cmd1_str_cant > 0)
	{
		while (++i < args->cmd1_str_cant)
			free(args->cmd1_split[i]);
	}
	i = -1;
	if (args->cmd2_str_cant > 0)
	{
		while (++i < args->cmd2_str_cant)
			free(args->cmd2_split[i]);
	}
	i = -1;
	if (routes->path_routes_cant > 0)
	{
		while (++i < routes->path_routes_cant)
		{		
			free(routes->path_routes_cmd1[i]);
			free(routes->path_routes_cmd2[i]);
		}
	}	
	free(args->cmd1_split);
	free(args->cmd2_split);
	free(routes->path_routes_cmd1);
	free(routes->path_routes_cmd2);
}
