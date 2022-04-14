/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:25:15 by jelorza-          #+#    #+#             */
/*   Updated: 2022/04/14 19:09:38 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<fcntl.h>

typedef struct args {
	char	*infile;
	char	*outfile;
	char	**cmd1_split;
	int		cmd1_str_cant;
	char	**cmd2_split;
	int		cmd2_str_cant;
	char	*cmd1;
	char	*cmd2;

}	t_pipe_args;

typedef struct routes {
	char	**path_routes_cmd1;
	char	**path_routes_cmd2;
	int		path_routes_cant;
	int		x1;
	int		x2;

}	t_pipe_routes;

typedef struct fds {
	int	fd_infile;
	int	fd_outfile;
	int	fd1[2];

}	t_pipe_fds;

void	ft_clean_args(char **argv, t_pipe_args *data);
void	ft_printf(t_pipe_args *args);
char	**ft_split(char *str, char c);
char	*ft_split_words(char *str, char c);
int		ft_substr_counter(char *str, char c);
int		ft_char_counter(char *str, char c, int i);
void	ft_path_routes(char **env, t_pipe_routes *routes, t_pipe_args *data);
int		ft_strncmp(char *s1, char *s2, int n);
void	ft_free(t_pipe_args *args, t_pipe_routes *routes);
int		ft_strlen(char *str);
int		ft_process_path(char	*env, t_pipe_routes *routes, t_pipe_args *data);
void	ft_process_path_end(t_pipe_routes *routes,
			char **temp2, t_pipe_args *data);
char	*ft_join(char *src1, char *src2);
void	ft_join_cmds(t_pipe_args *data);
char	*ft_substr(char *str, int start, int end);
void	ft_acces(t_pipe_args *data, t_pipe_routes *routes);
void	ft_process_pipe(t_pipe_args *data, t_pipe_routes *routes, char **env);
int		ft_fork1(t_pipe_routes *routes, t_pipe_fds *fds,
			char **env, t_pipe_args *data);
int		ft_fork2(t_pipe_routes *routes, t_pipe_fds *fds,
			char **env, t_pipe_args *data);
#endif
