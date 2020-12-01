/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_gE.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:03:15 by romain            #+#    #+#             */
/*   Updated: 2020/12/01 11:18:40 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_parsing.h"

static int	size_display_ge(t_doub *doub, t_flags *flags)
{
	int	is_exponent;

	is_exponent = 4;
	if (doub->isnull)
		is_exponent = 0;
        if (doub->strdoub[0] == '0' && doub->point == 1)
                flags->precision_val++;
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
                return (flags->precision_val + 1 + is_exponent); 
        else if (flags->precision_val <= doub->point)
		return (flags->precision_val + is_exponent); 
	return (flags->precision_val + 1 + is_exponent); 
}	

static void	write_float_ge(t_doub *doub, t_flags *flags)
{
	int	decisize;

	decisize = doub->size - doub->point;
	if (doub->isnull && !(flags->bw_flags & CROISI))
	{
		write_char_buffer('0', 1);
		return ;
	}
	else if (flags->precision_val <= doub->point)
	{
		write_str_buffer(doub->strdoub, flags->precision_val);
		if (flags->precision_val == doub->point && flags->bw_flags & CROISI)
			write_char_buffer('.', 1);
	}
	else
	{
		write_str_buffer(doub->strdoub, doub->point);
		write_char_buffer('.', 1);
		if (doub->size < flags->precision_val)
			write_str_buffer(&doub->strdoub[doub->point], decisize);
		else
			write_str_buffer(&doub->strdoub[doub->point], flags->precision_val - doub->point);
		write_char_buffer('0', flags->precision_val - doub->size);
	}
	write_exponent(doub->exponent);
}

void	lobby_write_gE(t_doub *doub, t_flags *flags)
{
        if (doub->sign == '+')
                write_double_pos(flags, size_display_ge(doub, flags), doub, write_float_ge);
        else
                write_double_neg(flags, size_display_ge(doub, flags), doub, write_float_ge);
}

