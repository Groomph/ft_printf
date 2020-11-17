/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:58:50 by romain            #+#    #+#             */
/*   Updated: 2020/11/17 20:21:29 by rsanchez         ###   ########.fr       */
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

static int	second_pars(char *str, int i, t_pars *pars, va_list *param)
{
	if (str[i] <= '9' && str[i] >= '1')
		pars->field_width_val = my_atoi(str, &i);
	else if (str[i] == '*')
	{
		pars->field_width_val = va_arg(*param, int);
		i++;
	}
	else if (str[i] == '.')
	{
		pars->precision_bool = 1;
		i++;
		if (str[i] == '*')
		{
			i++;
			pars->precision_val = va_arg(*param, int);
		}
		else
			pars->precision_val = my_atoi(str, &i);
	}
	else if (str[i] == ' ')
		i++;
	else
		return (i);
	return (second_pars(str, i, pars, param));
}

static int	first_pars(char *str, int i, t_pars *pars)
{
	if (str[i] == '-')
		pars->boundary_left = 1;
	else if (str[i] == '0')
		pars->zero_padded = 1;
	else
		return (i);
	return (first_pars(str, i + 1, pars));
}

void		init_struct(t_pars *pars)
{
	pars->boundary_left = 0;
	pars->zero_padded = 0;
	pars->precision_bool = 0;
	pars->precision_val = 0;
	pars->field_width_val = 0;
}

int			ft_printf_parsing(char *str, va_list *param, int *count)
{
	t_pars	pars;
	int		i;
	int		tmp;
	va_list	param2;

	init_struct(&pars);
	i = 0;
	va_copy(param2, *param);
	if ((tmp = first_pars(str, 1, &pars)) == -1)
		return (0);
	i += tmp;
	if ((tmp = second_pars(&str[i], 0, &pars, &param2)) == -1)
		return (0);
	i += tmp;
	if (str[i] != 'u' && str[i] != 'i' && str[i] != 'p'
			&& str[i] != '%' && str[i] != 'c' && str[i] != 's'
			&& str[i] != 'd' && str[i] != 'x' && str[i] != 'X')
		return (0);
	pars.convert_char = str[i++];
	*count += ft_printf_print(&pars, &param2);
	va_copy(*param, param2);
	return (i);
}
