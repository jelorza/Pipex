/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorza- <jelorza-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:59:27 by jelorza-          #+#    #+#             */
/*   Updated: 2022/04/10 18:02:54 by jelorza-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char *str, int start, int end)

{
	char	*ret;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	ret = malloc(sizeof(char) * (end - start) + 1);
	if (ret == NULL)
		return (NULL);
	if (start >= ft_strlen(str) || end == 0)
	{
		*ret = 00;
		return (ret);
	}
	else
	{
		while (start < end)
		{
			ret[i] = str[start];
			start++;
			i++;
		}
		ret[i] = 00;
		return (ret);
	}
}

char	*ft_join(char *src1, char *src2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	str = malloc (sizeof(char) * (ft_strlen(src1) + ft_strlen(src2) + 1));
	while (src1[++i])
		str[i] = src1[i];
	j = 0;
	while (src2[j])
	{
		str[i] = src2[j];
		i++;
		j++;
	}
	str[i] = 00;
	return (str);
}	

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (00);
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
