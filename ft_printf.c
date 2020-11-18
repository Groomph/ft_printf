/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/11/18 12:21:07 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	param;
	int		count;

	i = 0;
	count = 0;
	va_start(param, str);
	while (str[i])
	{
		if (str[i] == '%')
			i += ft_printf_parsing((char*)&str[i], &param, &count);
		if (str[i] && str[i] != '%')
		{
			write(1, &str[i], 1);
			i++;
			count++;
		}
	}
	va_end(param);
	return (count);
}
