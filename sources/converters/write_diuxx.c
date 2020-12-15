/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_diuxx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:37:07 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:37:09 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					set_comp_num(t_pars *pars)
{
	if (pars->precision_val > pars->size_str)
	{
		pars->zero_before += (pars->precision_val - pars->size_str);
		pars->field_width_val -= pars->precision_val + pars->size_extra;
	}
	else
		pars->field_width_val -= (pars->size_str + pars->size_extra);
	add_sign_numeric(pars, pars->sign);
	if (pars->field_width_val > 0)
		fill_width(pars, pars->field_width_val);
	write_into_buffer(pars, 0);
}

void					lobby_numeric_converter(unsigned long long int nb,
							char *base, t_pars *pars, int sizeb)
{
	char	tab[50];

	if (pars->bw_flags & ZERO && pars->bw_flags & PRECIS)
		pars->bw_flags &= ~(ZERO);
	else if (!(pars->bw_flags & PRECIS))
	{
		pars->bw_flags |= PRECIS;
		pars->precision_val = 1;
	}
	pars->str = tab;
	pars->size_str = 0;
	if (!((pars->bw_flags & PRECIS) && pars->precision_val == 0 && nb == 0))
		pars->size_str = utoa_base(nb, tab, base, sizeb);
	set_comp_num(pars);
}

void					write_di(va_list *param, t_pars *pars)
{
	long long int	nb;

	if (pars->bw_flags & LLLL)
		nb = va_arg(*param, long long int);
	else if (pars->bw_flags & LL)
		nb = va_arg(*param, long int);
	else
		nb = va_arg(*param, int);
	if (pars->bw_flags & HHHH)
		nb = (char)nb;
	else if (pars->bw_flags & HH)
		nb = (short)nb;
	if (nb < 0)
	{
		pars->sign = '-';
		lobby_numeric_converter((unsigned long long int)-nb,
				"0123456789", pars, 10);
		return ;
	}
	if (pars->bw_flags & SPACE || pars->bw_flags & PLUS)
		pars->sign = '+';
	lobby_numeric_converter((unsigned long long int)nb,
			"0123456789", pars, 10);
}

void					write_u(va_list *param, t_pars *pars)
{
	unsigned long long int	nb;

	nb = get_unsigned_param(param, pars);
	lobby_numeric_converter(nb, "0123456789", pars, 10);
}

void					write_xx(va_list *param, t_pars *pars)
{
	unsigned long long int	nb;
	char					tab[2];

	nb = get_unsigned_param(param, pars);
	if (nb && pars->bw_flags & CROISI)
	{
		tab[0] = '0';
		tab[1] = pars->convert_char;
		pars->extra_before = tab;
		pars->size_extra = 2;
	}
	if (pars->convert_char == 'X')
		lobby_numeric_converter(nb, "0123456789ABCDEF", pars, 16);
	else
		lobby_numeric_converter(nb, "0123456789abcdef", pars, 16);
}
