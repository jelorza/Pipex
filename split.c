/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:37:33 by jelorza-          #+#    #+#             */
/*   Updated: 2022/04/10 17:58:58 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	**ft_split(char *str, char c)
{
	char	**bi_str_cmd;
	int		i;
	int		sub_str;

	i = 0;
	sub_str = ft_substr_counter(str, c);
	bi_str_cmd = malloc(sizeof (char **) * sub_str + 1);
	while (i < sub_str)
	{
		bi_str_cmd[i] = ft_split_words(str, c);
		i++;
	}
	bi_str_cmd[i] = 00;
	return (bi_str_cmd);
}

char	*ft_split_words(char *str, char c)
{
	char		*str2;
	static int	i;
	int			j;
	int			char_cant;

	j = 0;
	while (str[i] && str[i] == c)
		i++;
	char_cant = ft_char_counter(str, c, i);
	str2 = malloc(sizeof(char) * char_cant + 1);
	if (!str2)
		return (0);
	while (j < char_cant)
	{
		str2[j] = str[i];
		j++;
		i++;
	}
	str2[j] = 00;
	while (str[i] && str[i] == c)
		i++;
	if (i == ft_strlen(str))
		i = 0;
	return (str2);
}

int	ft_char_counter(char *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

int	ft_substr_counter(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && str[i] != c)
		{
			i++;
		}
		if (str[i - 1] != c)
			count++;
	}
	return (count);
}
