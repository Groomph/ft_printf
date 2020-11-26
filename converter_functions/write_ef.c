/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ef.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/26 01:54:30 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	write_double_pos(t_flags *flags, int sizetoprint, char *temp)
{
	if (flags->bw_flags & MINUS)
	{
		write_str_buffer(temp, sizetoprint);
		write_char_buffer(' ', flags->field_width_val - sizetoprint);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', flags->field_width_val - sizetoprint);
		else
			write_char_buffer(' ', flags->field_width_val - sizetoprint);
		write_str_buffer(temp, sizetoprint);
	}
}

static void	write_double_neg_nobound(t_flags *flags, int sizetoprint, char *temp)
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
	write_str_buffer(temp, sizetoprint);
}

static void	write_double_neg(t_flags *flags, int sizetoprint, char *temp)
{
	int	space_toprint;
	
	if (!(flags->bw_flags & MINUS))
		write_double_neg_nobound(flags, sizetoprint, temp);
	else
	{
		space_toprint = flags->field_width_val - sizetoprint - 1;
		write_char_buffer('-', 1);
		write_str_buffer(temp, sizetoprint);
		write_char_buffer(' ', space_toprint);
	}
}

void	write_e(va_list *param, t_flags *flags)
{
	double	doub;
	int	sizetoprint;
	int	isneg;
	char	temp[100];

	doub = va_arg(*param, double);
	isneg = 0;
	if (doub <= 0.0 && ft_is_signed(doub))
	{
		isneg = 1;
		doub *= -1;
	}		
	sizetoprint = write_double_expo(doub, flags, temp);
	if (isneg)
		write_double_neg(flags, sizetoprint, temp);
	else	
		write_double_pos(flags, sizetoprint, temp);
}

void	write_f(va_list *param, t_flags *flags)
{
        double  doub;
        int     sizetoprint;
	int	isneg;
	char	temp[100];

        doub = va_arg(*param, double);
	isneg = 0;
	if (doub <= 0.0 && ft_is_signed(doub))
	{
		isneg = 1;
		doub *= -1;
	}		
	sizetoprint = write_double_regular(doub, flags, temp, NULL);
	if (isneg)
		write_double_neg(flags, sizetoprint, temp);
	else	
		write_double_pos(flags, sizetoprint, temp);
}
