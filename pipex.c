/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:03:22 by jelorza-          #+#    #+#             */
/*   Updated: 2022/04/11 20:48:53 by jelorza-         ###   ########.fr       */
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
		write (1, "", 25);
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
			ft_process_path(env[i], routes, data);
		i++;
	}
}

int	ft_process_path(char *env, t_pipe_routes *routes, t_pipe_args *data)
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
	ft_process_path_end(routes, temp2, data);
	return (0);
}

void	ft_process_path_end(t_pipe_routes *routes,
	char **temp2, t_pipe_args *data)
{
	int	i;

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
}
