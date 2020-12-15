/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:33:30 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:33:33 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		fill_width(t_pars *pars, int remains)
{
	if (pars->bw_flags & MINUS)
		pars->space_after += remains;
	else if (pars->bw_flags & ZERO)
		pars->zero_before += remains;
	else
		pars->space_before += remains;
}

void		add_sign_numeric(t_pars *pars, char sign)
{
	if (sign == '-' || (pars->bw_flags & PLUS && sign))
	{
		pars->sign = sign;
		pars->print_sign = 1;
		pars->field_width_val--;
	}
	else if (sign == '+' && pars->bw_flags & SPACE)
	{
		pars->space_before++;
		pars->field_width_val--;
	}
}

static int	atoi_pars(const char *str, int *i)
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

int			field_width(t_pars *pars, va_list *param, const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '*')
	{
		pars->field_width_val = va_arg(*param, int);
		if (pars->field_width_val < 0)
		{
			pars->bw_flags |= MINUS;
			pars->field_width_val *= -1;
		}
		return (1);
	}
	pars->field_width_val = atoi_pars(str, &i);
	return (i);
}

int			precision(t_pars *pars, va_list *param, const char *str)
{
	int	i;

	i = 1;
	if (str[i] == '*')
	{
		i++;
		pars->precision_val = va_arg(*param, int);
	}
	else
		pars->precision_val = atoi_pars(str, &i);
	if (pars->precision_val >= 0)
		pars->bw_flags |= PRECIS;
	else
		pars->precision_val = 0;
	return (i);
}
