/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:30:13 by jelorza-          #+#    #+#             */
/*   Updated: 2022/04/11 20:30:18 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(t_pipe_args *args, t_pipe_routes *routes)
{
	int	i;

	i = -1;
	while (++i < args->cmd1_str_cant)
		free(args->cmd1_split[i]);
	i = -1;
	while (++i < args->cmd2_str_cant)
		free(args->cmd2_split[i]);
	i = -1;
	while (++i < routes->path_routes_cant)
	{		
		free(routes->path_routes_cmd1[i]);
		free(routes->path_routes_cmd2[i]);
	}
	free(args->cmd1_split);
	free(args->cmd2_split);
	free(routes->path_routes_cmd1);
	free(routes->path_routes_cmd2);
}
