/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez </var/mail/rsanchez>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:37:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/11/23 04:49:13 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void		signed_nobound(t_flags *flags, unsigned long nb, char *base,
																	int sizeb)
{
	int	maxprint;
	int	zero_toprint;
	int	space_toprint;
	int	sizetoprint;

	sizetoprint = my_utoa_len(nb, sizeb, flags);
	maxprint = sizetoprint;
	if (flags->precision_bool && sizetoprint < flags->precision_val)
		maxprint = flags->precision_val;
	zero_toprint = maxprint - sizetoprint;
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
	write_char_buffer('0', zero_toprint);
	write_base_recurs(nb, base, sizeb, sizetoprint);
}

static void		signed_bound(t_flags *flags, unsigned long nb, char *base,
																int sizeb)
{
	int	maxprint;
	int	zero_toprint;
	int	space_toprint;
	int	sizetoprint;

	sizetoprint = my_utoa_len(nb, sizeb, flags);
	if (!flags->boundary_left)
		signed_nobound(flags, nb, base, sizeb);
	else
	{
		maxprint = sizetoprint;
		if (flags->precision_bool && sizetoprint < flags->precision_val)
			maxprint = flags->precision_val;
		zero_toprint = maxprint - sizetoprint;
		space_toprint = flags->field_width_val - maxprint - 1;
		write_char_buffer('-', 1);
		write_char_buffer('0', zero_toprint);
		write_base_recurs(nb, base, sizeb, sizetoprint);
		write_char_buffer(' ', space_toprint);
	}
}

static void		unsigned_bound(t_flags *flags, unsigned long nb, char *base,
																int sizeb)
{
	int	maxprint;
	int	zero_toprint;
	int	space_toprint;
	int	sizetoprint;

	sizetoprint = my_utoa_len(nb, sizeb, flags);
	maxprint = sizetoprint;
	if (flags->precision_bool && sizetoprint < flags->precision_val)
		maxprint = flags->precision_val;
	zero_toprint = maxprint - sizetoprint;
	space_toprint = flags->field_width_val - maxprint;
	write_char_buffer('0', zero_toprint);
	write_base_recurs(nb, base, sizeb, sizetoprint);
	write_char_buffer(' ', space_toprint);
}

void			unsigned_noboun(t_flags *flags, unsigned long nb, char *base,
																int sizeb)
{
	int	maxprint;
	int	zero_toprint;
	int	space_toprint;
	int	sizetoprint;

	if (flags->boundary_left)
		unsigned_bound(flags, nb, base, sizeb);
	else
	{
		sizetoprint = my_utoa_len(nb, sizeb, flags);
		maxprint = sizetoprint;
		if (flags->precision_bool && sizetoprint < flags->precision_val)
			maxprint = flags->precision_val;
		space_toprint = 0;
		if (!flags->precision_bool && flags->zero_padded)
			zero_toprint = flags->field_width_val - sizetoprint;
		else
		{
			zero_toprint = maxprint - sizetoprint;
			space_toprint = flags->field_width_val - maxprint;
		}
		write_char_buffer(' ', space_toprint);
		write_char_buffer('0', zero_toprint);
		write_base_recurs(nb, base, sizeb, sizetoprint);
	}
}

void			write_di(va_list *param, t_flags *flags)
{
	int	nb;

	nb = va_arg(*param, int);
	if (nb >= 0)
		unsigned_noboun(flags, nb, "0123456789", 10);
	else
		signed_bound(flags, (unsigned int)-nb, "0123456789", 10);
}
