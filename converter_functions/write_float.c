/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:34:27 by romain            #+#    #+#             */
/*   Updated: 2020/12/01 01:30:41 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_parsing/float_parsing.h"

void	write_double_pos(t_flags *flags, int sizetoprint, t_doub *doub, void (*f)(t_doub*, t_flags*))
{
	if (flags->bw_flags & MINUS)
	{
		f(doub, flags);
		write_char_buffer(' ', flags->field_width_val - sizetoprint);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', flags->field_width_val - sizetoprint);
		else
			write_char_buffer(' ', flags->field_width_val - sizetoprint);
		f(doub, flags);
	}
}

static void	write_double_neg_nobound(t_flags *flags, int sizetoprint, t_doub *doub, void (*f)(t_doub*, t_flags*))
{
	int	space_toprint;

	space_toprint = flags->field_width_val - sizetoprint - 1;
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
	f(doub, flags);
}

void	write_double_neg(t_flags *flags, int sizetoprint, t_doub *doub, void (*f)(t_doub*, t_flags*))
{
	int	space_toprint;
	
	if (!(flags->bw_flags & MINUS))
		write_double_neg_nobound(flags, sizetoprint, doub, f);
	else
	{
		space_toprint = flags->field_width_val - sizetoprint - 1;
		write_char_buffer('-', 1);
		f(doub, flags);
		write_char_buffer(' ', space_toprint);
	}
}
