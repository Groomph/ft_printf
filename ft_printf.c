/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/11/22 22:17:15 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list		param;
	int		tmp;

	init_buffer();
	i = 0;
	tmp = 0;
	va_start(param, str);
	while (str[i])
	{
		if (str[i] == '%')
			tmp = ft_printf_parsing((char*)&str[i], &param);
		if (tmp == 0)
			write_char_buffer(str[i++], 1);
		else
		{
			while (str[i] && tmp > 0)
			{
				i++;
				tmp--;
			}
		}
	}
	va_end(param);
	print_buffer(1);
	return (send_totalsize());
}
