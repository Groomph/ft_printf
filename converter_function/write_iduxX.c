/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_iduxX.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez </var/mail/rsanchez>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:37:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/11/22 22:17:56 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
		
void	write_signed_boundary_no(t_flags *flags, unsigned long nb, char *base, int sizebase)
{
	int	maxprint;
	int	_0_toprint;
	int	space_toprint;
	int	sizetoprint;

	sizetoprint = my_utoa_len(nb, sizebase, flags);
	maxprint = sizetoprint;
	if (flags->precision_bool && sizetoprint < flags->precision_val)
	       maxprint = flags->precision_val;
	_0_toprint = maxprint - sizetoprint;
	space_toprint = flags->field_width_val - maxprint - 1;
	if (flags->zero_padded && !flags->precision_bool)
	{
		write_char_buffer('-', 1);
		write_char_buffer('0', space_toprint);
	}
	else
	{
		write_char_buffer(' ', space_toprint);
		write_char_buffer('-', 1);
	}
	write_char_buffer('0', _0_toprint);
	write_base_recurs(nb, base, sizebase, sizetoprint);
}

void	write_signed_boundary(t_flags *flags, unsigned long nb, char *base, int sizebase)
{
	int	maxprint;
	int	_0_toprint;
	int	space_toprint;
	int	sizetoprint;

	sizetoprint = my_utoa_len(nb, sizebase, flags);
	if (!flags->boundary_left)
		write_signed_boundary_no(flags, nb, base, sizebase);
	else
	{
		maxprint = sizetoprint;
		if (flags->precision_bool && sizetoprint < flags->precision_val)
			maxprint = flags->precision_val;
		_0_toprint = maxprint - sizetoprint;
		space_toprint = flags->field_width_val - maxprint - 1;
		write_char_buffer('-', 1);
		write_char_buffer('0', _0_toprint);
		write_base_recurs(nb, base, sizebase, sizetoprint);
		write_char_buffer(' ', space_toprint);
	}
}

void	write_unsigned_boundary(t_flags *flags, unsigned long nb, char *base, int sizebase)
{
	int	maxprint;
	int	_0_toprint;
	int	space_toprint;
	int	sizetoprint;

	sizetoprint = my_utoa_len(nb, sizebase, flags);
	maxprint = sizetoprint;
	if (flags->precision_bool && sizetoprint < flags->precision_val)
		maxprint = flags->precision_val;
	_0_toprint = maxprint - sizetoprint;
	space_toprint = flags->field_width_val - maxprint;
	write_char_buffer('0', _0_toprint);
	write_base_recurs(nb, base, sizebase, sizetoprint);
	write_char_buffer(' ', space_toprint);
}

void	write_unsigned_digit(t_flags *flags, unsigned long nb, char *base, int sizebase)
{
	int	maxprint;
	int	_0_toprint;
	int	space_toprint;
	int	sizetoprint;

	if (flags->boundary_left)
		write_unsigned_boundary(flags, nb, base, sizebase);
	else
	{
		sizetoprint = my_utoa_len(nb, sizebase, flags);
		maxprint = sizetoprint;
		if (flags->precision_bool && sizetoprint < flags->precision_val)
			maxprint = flags->precision_val;
		if (!flags->precision_bool && flags->zero_padded)
		{
			_0_toprint = flags->field_width_val - sizetoprint;
			space_toprint = 0;
		}
		else
		{
			_0_toprint = maxprint - sizetoprint;
			space_toprint = flags->field_width_val - maxprint;
		}
		write_char_buffer(' ', space_toprint);
		write_char_buffer('0', _0_toprint);
		write_base_recurs(nb, base, sizebase, sizetoprint);
	}
}

void	write_u(va_list *param, t_flags *flags)
{
	long	nb;

	nb = va_arg(*param, long);
	write_unsigned_digit(flags, nb, "0123456789", 10);
}

void	write_di(va_list *param, t_flags *flags)
{
	int	nb;
	
	nb = va_arg(*param, int);
	if (nb >= 0)
		write_unsigned_digit(flags, nb, "0123456789", 10);
	else
		write_signed_boundary(flags, (unsigned int)-nb, "0123456789", 10);
}

void	write_x(va_list *param, t_flags *flags)
{
	write_unsigned_digit(flags, va_arg(*param, unsigned long), "0123456789abcdef", 16);
}

void	write_X(va_list *param, t_flags *flags)
{
	write_unsigned_digit(flags, va_arg(*param, unsigned long), "0123456789ABCDEF", 16);
}


