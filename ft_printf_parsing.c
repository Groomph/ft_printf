/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:58:50 by romain            #+#    #+#             */
/*   Updated: 2020/11/20 16:48:32 by romain           ###   ########.fr       */
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

static int	second_pars(char *str, int i, t_buffer *buf, va_list *param)
{
	if (str[i] <= '9' && str[i] >= '1')
		buf->pars.field_width_val = my_atoi(str, &i);
	else if (str[i] == '*')
	{
		buf->pars.field_width_val = va_arg(*param, int);
		if (buf->pars.field_width_val < 0)
		{
			buf->pars.boundary_left = 1;
			buf->pars.field_width_val *= -1;
		}
		i++;
	}
	else if (str[i] == '.')
	{
		buf->pars.precision_bool = 1;
		i++;
		if (str[i] == '*')
		{
			i++;
			buf->pars.precision_val = va_arg(*param, int);
		}
		else
			buf->pars.precision_val = my_atoi(str, &i);
		buf->pars.precision_bool = buf->pars.precision_val < 0 ? 0 : buf->pars.precision_bool;
	}
	else if (str[i] == ' ')
		i++;
	else
		return (i);
	return (second_pars(str, i, buf, param));
}

static int	first_pars(char *str, int i, t_buffer *buf)
{
	if (str[i] == '-')
		buf->pars.boundary_left = 1;
	else if (str[i] == '0')
		buf->pars.zero_padded = 1;
	else
		return (i);
	return (first_pars(str, i + 1, buf));
}

void		init_struct(t_buffer *buf)
{
	buf->pars.boundary_left = 0;
	buf->pars.zero_padded = 0;
	buf->pars.precision_bool = 0;
	buf->pars.precision_val = 0;
	buf->pars.field_width_val = 0;
	buf->pars.convert_char = 0;
}

int			ft_printf_parsing(char *str, t_buffer *buf, va_list *param)
{
	int		i;
	int		tmp;
	va_list	param2;

	init_struct(buf);
	i = 0;
	va_copy(param2, *param);
	if ((tmp = first_pars(str, 1, buf)) == -1)
		return (0);
	i += tmp;
	if ((tmp = second_pars(&str[i], 0, buf, &param2)) == -1)
		return (0);
	i += tmp;
	if (str[i] != 'u' && str[i] != 'i' && str[i] != 'p'
			&& str[i] != '%' && str[i] != 'c' && str[i] != 's'
			&& str[i] != 'd' && str[i] != 'x' && str[i] != 'X')
		return (0);
	buf->pars.convert_char = str[i];
	i++;
//printf("%d %d %d %d %d...\n\n", pars.boundary_left, pars.zero_padded, pars.precision_bool, pars.precision_val, pars.field_width_val);
	ft_printf_print(buf, &param2);
	va_copy(*param, param2);
	return (i);
}
