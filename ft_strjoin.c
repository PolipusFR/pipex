/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:58:19 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/19 17:49:25 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	int			j;
	char		*ret;

	j = 0;
	i = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc (i * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	if (s2 != NULL)
	{
		while (s2[j])
		{
			ret[i + j] = s2[j];
			j++;
		}
	}
	ret [i + j] = '\0';
	return (ret);
}
