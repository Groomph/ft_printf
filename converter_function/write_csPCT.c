/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_csPCT.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/22 19:12:27 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	write_char_null(t_flags *flags)
{
	if (flags->boundary_left)
	{
		write_char_buffer('\0', 1);
		write_char_buffer(' ', flags->field_width_val - 1);
	}
	else
	{
		write_char_buffer(' ', flags->field_width_val - 1);
		write_char_buffer('\0', 1);
	}
}

static void	write_string(t_flags *flags, char *str, char *strnull)
{
	int	sizetoprint;

	if (!str)
		str = strnull;
	sizetoprint = my_my_strlen(str);
	if (flags->precision_bool && sizetoprint > flags->precision_val)
		sizetoprint = flags->precision_val;
	if (flags->boundary_left)
	{
		write_str_buffer(str, sizetoprint);
		write_char_buffer(' ', flags->field_width_val - sizetoprint);
	}
	else
	{
		if (flags->zero_padded)
			write_char_buffer('0', flags->field_width_val - sizetoprint);
		else
			write_char_buffer(' ', flags->field_width_val - sizetoprint);
		write_str_buffer(str, sizetoprint);
	}
}

void	write_c(va_list *param, t_flags *flags)
{
	char		c[2];

	c[0] = (char)va_arg(*param, int);
	c[1] = '\0';
	if (c[0] == '\0')
		return (write_char_null(flags));
	if (flags->precision_val == 0 && flags->precision_bool)
		flags->precision_val = 1;
	write_string(flags, c, "");
}

void	write_s(va_list *param, t_flags *flags)
{
	write_string(flags, va_arg(*param, char*), "(null)");
}

void	write_PCT(t_flags *flags)
{
	if (flags->precision_val == 0 && flags->precision_bool)
		flags->precision_val = 1;
	write_string(flags, "%", "");
}
