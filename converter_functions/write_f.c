/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/24 00:08:15 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>

void	write_lobby_pos(double doub, t_flags *flags)
{
	long long int	intpart;
	long long int	multi;
	int			i;
	int			limit;

	i = -1;
	limit = 6;
	multi = 1;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	if (limit == 0)
		doub += 0.5;
	intpart = doub;
	write_base_recurs(intpart, "0123456789", 10, 50);
	if (limit == 0)
		return ;
	write_char_buffer('.', 1);
	doub += intpart;
	while (++i < limit)
		multi *= 10;
	doub *= multi;
	doub += 0.5;
	intpart = doub;
	write_base_recurs(intpart, "0123456789", 10, limit);
}


void	write_lobby_neg(double doub, t_flags *flags)
{
	long long int	intpart;
	long long int	multi;
	int			i;
	int			limit;

	i = -1;
	limit = 6;
	multi = 1;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	if (limit == 0)
		doub -= 0.5;
	intpart = doub;
	intpart *= -1;
	write_base_recurs(intpart, "0123456789", 10, 50);
	if (limit == 0)
		return ;
	write_char_buffer('.', 1);
	doub += intpart;
	while (++i < limit)
		multi *= 10;
	doub *= multi;
	doub -= 0.5;
	intpart = doub;
	intpart *= -1;
	write_base_recurs(intpart, "0123456789", 10, limit);
}
/*

	long long int	intpart;
	int			i;
	int			limit;

	i = -1;
	limit = 6;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	if (limit == 0)
	{
		if (limit >= 0)	
			doub += 0.5;
		else
			doub -= 0.5;
	}	
	intpart = (long int)doub;
	write_base_recurs(intpart, "0123456789", 10, 50);
	if (limit == 0)
		return ;
	write_char_buffer('.', 1);
	doub -= intpart;
	while (++i < limit)
	{
		doub *= 10;	
		if (i + 1 == limit)
		{
			if (limit >= 0)	
				doub += 0.5;
			else
				doub -= 0.5;
		}	
	}
	intpart = doub;
	write_base_recurs(intpart, "0123456789", 10, limit);
	
		doub -= intpart;
		doub *= 10;
		if (i + 1 < limit)
			intpart = (long int)doub;
		else
			intpart = (long int)(doub + 0.5);
		//printf("%li\n", intpart);
		//write_base_recurs(intpart, "0123456789", 10, 50);
		if (intpart == 10)
		{
			write_str_buffer("test", 4);
			write_str_buffer(&"00102030405060708090"[2], 2);
			i++;
		}
		else
		write_char_buffer("0123456789"[intpart], 1);
	}
}*/

void	write_double_pos(double doub, t_flags *flags, int sizetoprint)
{
	if (flags->bw_flags & MINUS)
	{
		write_lobby_pos(doub, flags);
		write_char_buffer(' ', flags->field_width_val - sizetoprint);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', flags->field_width_val - sizetoprint);
		else
			write_char_buffer(' ', flags->field_width_val - sizetoprint);
		write_lobby_pos(doub, flags);
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
	write_lobby_neg(doub, flags);
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
		write_lobby_neg(doub, flags);
		write_char_buffer(' ', space_toprint);
	}
}

void	write_f(va_list *param, t_flags *flags)
{
	double	doub;
	long int	tmp;
	int	sizetoprint;

	doub = va_arg(*param, double);
	tmp = doub < 0 ? -doub : doub;
	sizetoprint = my_utoa_len(tmp, 10, NULL);
	if (flags->bw_flags & PRECIS)
	       	sizetoprint += flags->precision_val == 0 ? 0 : 1 + flags->precision_val;
	else
		sizetoprint += 7;
	if (doub < 0)
		write_double_neg(doub, flags, sizetoprint + 1);
	else
		write_double_pos(doub, flags, sizetoprint);
}
