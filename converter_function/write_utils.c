/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:17:09 by romain            #+#    #+#             */
/*   Updated: 2020/11/20 12:28:19 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	my_strlen(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	my_utoa_len(unsigned long nb, int sizebase)
{
	int	i;

	i = 1;
	while (nb /= sizebase)
		i++;
	return (i);
}
