/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 07:04:38 by romain            #+#    #+#             */
/*   Updated: 2020/12/04 07:06:45 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*substr_free(char *str, size_t start, size_t len, int freestr)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (str && str[i])
		i++;
	if (!str || i < start)
	{
		if (!(temp = malloc(sizeof(char))))
			return (NULL);
		temp[0] = '\0';
		return (temp);
	}
	if (i < start + len)
		len = i - start;
	if (!(temp = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
		temp[i] = str[start + i];
	temp[i] = '\0';
	if (str && freestr)
		free(str);
	return (temp);
}
