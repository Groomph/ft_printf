/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/11/23 05:45:58 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list		param;

	init_buffer();
	i = 0;
	va_start(param, str);
	while (str && str[i])
	{
		while (str[i] && str[i] != '%')
			i++;
		write(str, i);
		str = &str[i];
		i = 0;
		if (str[i] == '%')
			i += ft_printf_parsing((char*)&str[i], &param);
	}
	va_end(param);
	print_buffer(1);
	return (send_totalsize());
}
