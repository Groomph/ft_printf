/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/24 04:43:13 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>
/*
void	write_lobby_double(double doub, t_flags *flags)
{
	long long int	intpart;
	int			i;
	int			limit;

	i = -1;
	limit = 6;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	if (limit == 0)
		doub += 0.5;
	intpart = doub;
	write_base_recurs(intpart, "0123456789", 10, 50);
	if (limit == 0)
		return ;
	write_char_buffer('.', 1);
	doub -= intpart;
	intpart = 1;
	while (++i < limit)
		intpart *= 10;
	doub *= intpart;
	doub += 0.50;
	intpart = doub;
	write_base_recurs(intpart, "0123456789", 10, limit);
}
*/

void	write_decimal(double doub, int limit)
{
	int	i;
	int multi;

	i = -1;
	multi = 1;
	while (++i < 1 && i < limit)
		multi *= 10;
	doub *= multi;
	if (i == limit)
		doub += 0.50;
	multi = doub;
	write_char_buffer("0123456789"[multi], 1);
	if (limit > 1)
		write_decimal(doub - multi, limit - 1);
}

void	write_lobby_double(double doub, t_flags *flags)
{
	long int	intpart;
	int			limit;

	limit = 6;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	if (limit == 0)
		doub += 0.5;
	intpart = doub;
	write_base_recurs(intpart, "0123456789", 10, 50);
	if (limit == 0)
		return ;
	write_char_buffer('.', 1);
	doub -= intpart;
	write_decimal(doub, limit);
}

void	write_double_pos(double doub, t_flags *flags, int sizetoprint)
{
	if (flags->bw_flags & MINUS)
	{
		write_lobby_double(doub, flags);
		write_char_buffer(' ', flags->field_width_val - sizetoprint);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', flags->field_width_val - sizetoprint);
		else
			write_char_buffer(' ', flags->field_width_val - sizetoprint);
		write_lobby_double(doub, flags);
	}
}

void	write_double_neg_nobound(double doub, t_flags *flags, int sizetoprint)
{
	int	space_toprint;

	space_toprint = flags->field_width_val - sizetoprint;
	if (flags->bw_flags & ZERO)
	{
		write_char_buffer('-', 1);
		write_char_buffer('0', space_toprint);
	}
	else
	{
		write_char_buffer(' ', space_toprint);
		write_char_buffer('-', 1);
	}
	write_lobby_double(doub, flags);
}

void	write_double_neg(double doub, t_flags *flags, int sizetoprint)
{
	int	space_toprint;
	
	if (!(flags->bw_flags & MINUS))
		write_double_neg_nobound(doub, flags, sizetoprint);
	else
	{
		space_toprint = flags->field_width_val - sizetoprint;
		write_char_buffer('-', 1);
		write_lobby_double(doub, flags);
		write_char_buffer(' ', space_toprint);
	}
}

void	write_f(va_list *param, t_flags *flags)
{
	double	doub;
	int	neg;
	int	sizetoprint;

	doub = va_arg(*param, double);
	neg = doub < 0 ? 1 : 0;
	doub = doub < 0 ? -doub : doub;
	sizetoprint = my_utoa_len(doub, 10, NULL);
	if (flags->bw_flags & PRECIS)
	       	sizetoprint += flags->precision_val == 0 ? 0 : 1 + flags->precision_val;
	else
		sizetoprint += 7;
	if (neg)
		write_double_neg(doub, flags, sizetoprint + 1);
	else
		write_double_pos(doub, flags, sizetoprint);
}
