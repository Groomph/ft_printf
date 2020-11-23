/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ouxx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez </var/mail/rsanchez>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:53:37 by rsanchez          #+#    #+#             */
/*   Updated: 2020/11/23 04:53:39 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	write_o(va_list *param, t_flags *flags)
{
	unsigned_noboun(flags, va_arg(*param, unsigned long),
						"01234567", 8);
}

void	write_u(va_list *param, t_flags *flags)
{
	unsigned_noboun(flags, va_arg(*param, long), "0123456789", 10);
}

void	write_x(va_list *param, t_flags *flags)
{
	unsigned_noboun(flags, va_arg(*param, unsigned long),
						"0123456789abcdef", 16);
}

void	write_xx(va_list *param, t_flags *flags)
{
	unsigned_noboun(flags, va_arg(*param, unsigned long),
						"0123456789ABCDEF", 16);
}
