/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ouxx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez </var/mail/rsanchez>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:37:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/11/23 04:25:13 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	write_o(va_list *param, t_flags *flags)
{
	unsigned_noboun(flags, va_arg(*param, unsigned long),
						"012345678", 8);
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
