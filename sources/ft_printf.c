/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/12/10 09:49:37 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "buffer.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		i2;
	va_list	param;
	
	init_buffer();
	i = 0;
	i2 = 0;
	va_start(param, str);
	while (str && str[i])
	{
		while (str[i] && str[i] != '%')
			i++;
		write_str_buffer(&str[i2], i - i2);
		if (str[i] == '%')
			i += ft_printf_parsing(&str[i], &param);
		i2 = i;
	}
	va_end(param);
	print_buffer(1);
	return (send_totalsize());
}
