/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:27:47 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:27:50 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoin_free(char *str1, char *str2, int freestr1, int freestr2)
{
	size_t	i;
	size_t	i2;
	char	*temp;

	i = 0;
	i2 = 0;
	while (str1 && str1[i])
		i++;
	while (str2 && str2[i2])
		i2++;
	if (!(temp = malloc(sizeof(char) * (i + i2 + 1))))
		return (NULL);
	temp[i + i2] = '\0';
	while (i2-- > 0)
		temp[i + i2] = str2[i2];
	while (i-- > 0)
		temp[i] = str1[i];
	if (str1 && freestr1)
		free(str1);
	if (str2 && freestr2)
		free(str2);
	return (temp);
}
