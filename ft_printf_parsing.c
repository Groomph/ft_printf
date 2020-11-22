/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:58:50 by romain            #+#    #+#             */
/*   Updated: 2020/11/22 20:38:09 by rsanchez         ###   ########.fr       */
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

static int	second_flags(char *str, int i, t_flags *flags, va_list *param)
{
	if (str[i] <= '9' && str[i] >= '1')
		flags->field_width_val = my_atoi(str, &i);
	else if (str[i] == '*')
	{
		flags->field_width_val = va_arg(*param, int);
		if (flags->field_width_val < 0)
		{
			flags->boundary_left = 1;
			flags->field_width_val *= -1;
		}
		i++;
	}
	else if (str[i] == '.')
	{
		flags->precision_bool = 1;
		i++;
		if (str[i] == '*')
		{
			i++;
			flags->precision_val = va_arg(*param, int);
		}
		else
			flags->precision_val = my_atoi(str, &i);
		flags->precision_bool = flags->precision_val < 0 ? 0 : flags->precision_bool;
	}
	else if (str[i] == ' ')
		i++;
	else
		return (i);
	return (second_flags(str, i, flags, param));
}

static int	first_flags(char *str, int i, t_flags *flags)
{
	if (str[i] == '-')
		flags->boundary_left = 1;
	else if (str[i] == '0')
		flags->zero_padded = 1;
	else
		return (i);
	return (first_flags(str, i + 1, flags));
}

void		init_flags_struct(t_flags *flags)
{
	flags->boundary_left = 0;
	flags->zero_padded = 0;
	flags->precision_bool = 0;
	flags->precision_val = 0;
	flags->field_width_val = 0;
	flags->convert_char = 0;
}

int			ft_printf_parsing(char *str, va_list *param)
{
	int		i;
	int		tmp;
	va_list	param2;
	t_flags		flags;
	
	init_flags_struct(&flags);
	i = 0;
	va_copy(param2, *param);
	if ((tmp = first_flags(str, 1, &flags)) == -1)
		return (0);
	i += tmp;
	if ((tmp = second_flags(&str[i], 0, &flags, &param2)) == -1)
		return (0);
	i += tmp;
	if (str[i] != 'u' && str[i] != 'i' && str[i] != 'p'
			&& str[i] != '%' && str[i] != 'c' && str[i] != 's'
			&& str[i] != 'd' && str[i] != 'x' && str[i] != 'X')
		return (0);
	flags.convert_char = str[i];
	i++;
//printf("%d %d %d %d %d...\n\n", flags.boundary_left, flags.zero_padded, flags.precision_bool, flags.precision_val, flags.field_width_val);
	lobby_write_buffer(&param2, &flags);
	va_copy(*param, param2);
	return (i);
}
