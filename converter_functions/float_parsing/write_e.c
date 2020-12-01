/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:34:27 by romain            #+#    #+#             */
/*   Updated: 2020/12/01 11:08:54 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_parsing.h"

static int	size_display_e(t_doub *doub, t_flags *flags)
{
	int	is_point;
	int	is_exponent;
	
	is_point = 1;
	is_exponent = 4;
	if (flags->precision_val == 0 && !(flags->bw_flags & CROISI))
		is_point = 0;
	if (doub->isnull)
		is_exponent = 4;
	return (1 + flags->precision_val + is_point + is_exponent);
}

static void	write_float_e(t_doub *doub, t_flags *flags)
{
	int	decisize;

	decisize = doub->size - doub->point;
	if (!flags->precision_val)
	{
		write_str_buffer(doub->strdoub, doub->point);
		if (flags->bw_flags & CROISI)
			write_char_buffer('.', 1);
	}
	else
	{
		write_str_buffer(doub->strdoub, doub->point);
		write_char_buffer('.', 1);
		if (decisize < flags->precision_val)
		{
			write_str_buffer(&doub->strdoub[doub->point], decisize);
			write_char_buffer('0', flags->precision_val - decisize);
		}
		else
			write_str_buffer(&doub->strdoub[doub->point], flags->precision_val);
	}
	write_exponent(doub->exponent);
}

void	write_e(va_list *param, t_flags *flags)
{

	t_doub		doub;
	if (!(flags->bw_flags & PRECIS))
        {
	        flags->bw_flags |= PRECIS;
              flags->precision_val = 6;
	}
	doub.doub = va_arg(*param, double);
	init_struct_double(&doub);
	doub = find_exponent(doub, flags->precision_val + 1);
	if (doub.sign == '+')
		write_double_pos(flags, size_display_e(&doub, flags), &doub, write_float_e);
	else
		write_double_neg(flags, size_display_e(&doub, flags), &doub, write_float_e);
}
