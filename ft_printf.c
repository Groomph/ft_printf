/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/11/19 16:25:21 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	param;
	int		count;
	int		tmp;

	i = 0;
	count = 0;
	tmp = 0;
	va_start(param, str);
	while (str[i])
	{
		if (str[i] == '%')
			tmp = ft_printf_parsing((char*)&str[i], &param, &count);
		if (tmp == 0)
		{
			write(1, &str[i], 1);
			i++;
			count++;
		}
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
	return (count);
}
