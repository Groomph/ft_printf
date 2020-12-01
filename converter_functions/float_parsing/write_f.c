/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:34:27 by romain            #+#    #+#             */
/*   Updated: 2020/12/01 11:09:09 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_parsing.h"

static int	size_display_f(t_doub *doub, t_flags *flags)
{
	int	is_point;

	is_point = 1;
	if (flags->precision_val == 0 && !(flags->bw_flags & CROISI))
		is_point = 0;
	return (doub->point + flags->precision_val + is_point);
}

static void	write_float_f(t_doub *doub, t_flags *flags)
{
	int	decisize;

	decisize = doub->size - doub->point;
	round_float(doub, doub->point + flags->precision_val);
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
}

void	write_f(va_list *param, t_flags *flags)
{

	t_doub		doub;
	if (!(flags->bw_flags & PRECIS))
        {
	        flags->bw_flags |= PRECIS;
              flags->precision_val = 6;
	}
	doub.doub = va_arg(*param, double);
	init_struct_double(&doub);
	if (doub.sign == '+')
		write_double_pos(flags, size_display_f(&doub, flags), &doub, write_float_f);
	else
		write_double_neg(flags, size_display_f(&doub, flags), &doub, write_float_f);
}
