/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ef.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/27 09:26:23 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	write_double_pos(t_flags *flags, int size_toprint, char *temp)
{
	if (flags->bw_flags & MINUS)
	{
		write_str_buffer(temp, size_toprint);
		write_char_buffer(' ', flags->field_width_val - size_toprint);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', flags->field_width_val - size_toprint);
		else
			write_char_buffer(' ', flags->field_width_val - size_toprint);
		write_str_buffer(temp, size_toprint);
	}
}

static void	write_neg_nobound(t_flags *flags, int size_toprint, char *temp)
{
	int	space_toprint;

	space_toprint = flags->field_width_val - size_toprint - 1;
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
	write_str_buffer(temp, size_toprint);
}

void	write_double_neg(t_flags *flags, int size_toprint, char *temp)
{
	int	space_toprint;
	
	if (!(flags->bw_flags & MINUS))
		write_neg_nobound(flags, size_toprint, temp);
	else
	{
		space_toprint = flags->field_width_val - size_toprint - 1;
		write_char_buffer('-', 1);
		write_str_buffer(temp, size_toprint);
		write_char_buffer(' ', space_toprint);
	}
}

void	write_e(va_list *param, t_flags *flags)
{
	double	doub;
	int	size_toprint;
	int	is_neg;
	char	temp[100];
	int	exponent;

	doub = va_arg(*param, double);
	is_neg = 0;
	if (doub <= 0.0 && ft_is_signed(doub))
	{
		is_neg = 1;
		doub *= -1;
	}		
        if (!(flags->bw_flags & PRECIS))
	{
		flags->bw_flags |= PRECIS;
		flags->precision_val = 6;
	}
	size_toprint = write_double_expo(doub, flags, temp, &exponent);
	if (is_neg)
		write_double_neg(flags, size_toprint, temp);
	else	
		write_double_pos(flags, size_toprint, temp);
}

void	write_f(va_list *param, t_flags *flags)
{
        double  doub;
        int     size_toprint;
	int	is_neg;
	char	temp[100];
	int	exponent;

        doub = va_arg(*param, double);
	is_neg = 0;
	if (doub <= 0.0 && ft_is_signed(doub))
	{
		is_neg = 1;
		doub *= -1;
	}		
        if (!(flags->bw_flags & PRECIS))
	{
		flags->bw_flags |= PRECIS;
		flags->precision_val = 6;
	}
	size_toprint = write_double_regular(doub, flags, temp, &exponent);
	if (is_neg)
		write_double_neg(flags, size_toprint, temp);
	else	
		write_double_pos(flags, size_toprint, temp);
}
