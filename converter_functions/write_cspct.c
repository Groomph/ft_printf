/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cspct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/24 02:57:55 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	write_char_null(t_flags *flags)
{
	if (flags->bw_flags & MINUS)
	{
		write_char_buffer('\0', 1);
		write_char_buffer(' ', flags->field_width_val - 1);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', flags->field_width_val - 1);
		else	
			write_char_buffer(' ', flags->field_width_val - 1);
		write_char_buffer('\0', 1);
	}
}

static void	write_string(t_flags *flags, char *str, char *strnull)
{
	int	sizetoprint;
	int	spacing;

	if (!str)
		str = strnull;
	sizetoprint = my_my_strlen(str);
	if (flags->bw_flags & PRECIS && sizetoprint > flags->precision_val)
		sizetoprint = flags->precision_val;
	spacing = flags->field_width_val - sizetoprint;
	if (flags->bw_flags & MINUS)
	{
		write_str_buffer(str, sizetoprint);
		write_char_buffer(' ', spacing);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', spacing);
		else
			write_char_buffer(' ', spacing);
		write_str_buffer(str, sizetoprint);
	}
}

void		write_c(va_list *param, t_flags *flags)
{
	char		c[2];

	c[0] = (char)va_arg(*param, int);
	c[1] = '\0';
	if (c[0] == '\0')
		return (write_char_null(flags));
	if (flags->precision_val == 0 && flags->bw_flags & PRECIS)
		flags->precision_val = 1;
	write_string(flags, c, "");
}

void		write_s(va_list *param, t_flags *flags)
{
	write_string(flags, va_arg(*param, char*), "(null)");
}

void		write_pct(t_flags *flags)
{
	if (flags->precision_val == 0 && flags->bw_flags & PRECIS)
		flags->precision_val = 1;
	write_string(flags, "%", "");
}
