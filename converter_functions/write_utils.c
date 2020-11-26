/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:17:09 by romain            #+#    #+#             */
/*   Updated: 2020/11/26 01:15:32 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	write_base_recurs(unsigned long long pt, char *base, int sizeb, int sizetopr)
{
	if (pt / sizeb)
		write_base_recurs(pt / sizeb, base, sizeb, sizetopr - 1);
	if (sizetopr > 0)
		write_char_buffer(base[pt % sizeb], 1);
}

void	write_digit_str(unsigned long long int intpart, char *pt, int i)
{
        if (intpart / 10)
                write_digit_str(intpart / 10, pt, i - 1);
        pt[i] = intpart % 10 + '0';
}

int		my_my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		my_utoa_len(unsigned long long nb, int sizebase, t_flags *flags)
{
	int	i;

	if (flags && flags->bw_flags & PRECIS && flags->precision_val == 0 && nb == 0)
		return (0);
	i = 1;
	while (nb /= sizebase)
		i++;
	return (i);
}

int        ft_is_signed(long double lf)
{
	    return ((1.0 / lf) != (1.0 / (lf < 0 ? 1 : 0)));
}
