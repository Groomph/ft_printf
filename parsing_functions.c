/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:58:50 by romain            #+#    #+#             */
/*   Updated: 2020/11/23 03:45:46 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	my_atoi(char *str, int *i)
{
	unsigned int	nb;
	int				neg;

	neg = 1;
	nb = 0;
	if (str[*i] == '-')
	{
		neg = -1;
		(*i)++;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		nb *= 10;
		nb += str[*i] - '0';
		(*i)++;
	}
	return (nb * neg);
}

int	field_width(t_flags *flags, va_list *param, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '*')
	{	
		flags->field_width_val = va_arg(*param, int);
		if (flags->field_width_val < 0)
		{
			flags->boundary_left = 1;
			flags->field_width_val *= -1;
		}
		return (1);
	}
	flags->field_width_val = my_atoi(str, &i);
	return (i);
}

int	precision(t_flags *flags, va_list *param, char *str)
{
	int	i;

	i = 1;
	flags->precision_bool = 1;
	if (str[i] == '*')
	{
		i++;
		flags->precision_val = va_arg(*param, int);
	}
	else
		flags->precision_val = my_atoi(str, &i);
	flags->precision_bool = flags->precision_val < 0 ? 0 : flags->precision_bool;
	return (i);
}
