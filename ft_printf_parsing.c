/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:58:50 by romain            #+#    #+#             */
/*   Updated: 2020/11/23 15:03:22 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	second_flags(const char *str, int i, t_flags *flags, va_list *param)
{
	if (str[i] == '*' || (str[i] <= '9' && str[i] >= '1'))
		i += field_width(flags, param, &str[i]);
	else if (str[i] == '.')
		i += precision(flags, param, &str[i]);
	else if (str[i] == ' ')
		i++;
	else
		return (i);
	return (second_flags(str, i, flags, param));
}

static int	first_flags(const char *str, int i, t_flags *flags)
{
	if (str[i] == '-')
		flags->bw_flags |= MINUS;
	else if (str[i] == '0')
		flags->bw_flags |= ZERO;
	else
		return (i);
	return (first_flags(str, i + 1, flags));
}

static void	init_flags_struct(t_flags *flags)
{
	flags->bw_flags = 0;
	flags->precision_val = 0;
	flags->field_width_val = 0;
	flags->convert_char = 0;
}

int			ft_printf_parsing(const char *str, va_list *param)
{
	int		i;
	va_list		param2;
	t_flags		flags;
	
	init_flags_struct(&flags);
	va_copy(param2, *param);
	i = first_flags(str, 1, &flags);
	i += second_flags(&str[i], 0, &flags, &param2);
	if (str[i])
			flags.convert_char = str[i++];
	if (!lobby_write_buffer(&param2, &flags))
		write_str_buffer(str, i);
	else
		va_copy(*param, param2);
	return (i);
}
