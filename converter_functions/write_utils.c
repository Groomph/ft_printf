/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:17:09 by romain            #+#    #+#             */
/*   Updated: 2020/11/22 23:26:26 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	write_base_recurs(unsigned long pt, char *base, int sizeb, int sizetopr)
{
	if (pt / sizeb)
		write_base_recurs(pt / sizeb, base, sizeb, sizetopr - 1);
	if (sizetopr > 0)
		write_char_buffer(base[pt % sizeb], 1);
}

int		my_my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		my_utoa_len(unsigned long nb, int sizebase, t_flags *flags)
{
	int	i;

	if (flags && flags->precision_bool && flags->precision_val == 0 && nb == 0)
		return (0);
	i = 1;
	while (nb /= sizebase)
		i++;
	return (i);
}
