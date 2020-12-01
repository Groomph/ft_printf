/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_gF.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:03:15 by romain            #+#    #+#             */
/*   Updated: 2020/12/01 11:18:02 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_parsing.h"

static int	size_display_gf(t_doub *doub, t_flags *flags)
{
	if (!(flags->bw_flags & CROISI))
	{
		if (flags->precision_val < doub->size)
			flags->precision_val -=
			count_clean_zero(doub, flags->precision_val - 1, 1);
		else
			flags->precision_val = doub->size -
				count_clean_zero(doub, doub->size - 1, 1);
	}
	if (flags->precision_val == doub->point && flags->bw_flags & CROISI)
		return (flags->precision_val + 1);
	else if (flags->precision_val <= doub->point)
		return (flags->precision_val);
	return (flags->precision_val + 1);
}

static void		write_float_gf(t_doub *doub, t_flags *flags)
{
	if (flags->precision_val <= doub->point)
	{
		write_str_buffer(doub->strdoub, flags->precision_val);
		if (flags->precision_val == doub->point && flags->bw_flags & CROISI)
			write_char_buffer('.', 1);
		return ;
	}
	write_str_buffer(doub->strdoub, doub->point);
	write_char_buffer('.', 1);
	if (doub->size < flags->precision_val)
		write_str_buffer(&doub->strdoub[doub->point], doub->size - doub->point);
	else
		write_str_buffer(&doub->strdoub[doub->point], flags->precision_val - doub->point);
	write_char_buffer('0', flags->precision_val - doub->size);
}

void	write_g(va_list *param, t_flags *flags)
{
	t_doub	doub;
	t_doub	temp;
	int	size_toprint;
	
	if (!(flags->bw_flags & PRECIS))
	{
		flags->bw_flags |= PRECIS;
		flags->precision_val = 6;
	}
	else if (flags->precision_val == 0)
		flags->precision_val = 1;
	doub.doub = va_arg(*param, double);	
	init_struct_double(&doub);
	temp = find_exponent(doub, flags->precision_val);
	if (temp.exponent >= flags->precision_val || temp.exponent < -4)
	{
		lobby_write_gE(&temp, flags);
		return ;
	}
	if (doub.strdoub[0] == '0' && doub.point == 1)
		flags->precision_val++;
	round_float(&doub, flags->precision_val);
	size_toprint = size_display_gf(&doub, flags);
	if (doub.sign == '+')
		write_double_pos(flags, size_toprint, &doub, write_float_gf);
	else
		write_double_neg(flags, size_toprint, &doub, write_float_gf);
}
