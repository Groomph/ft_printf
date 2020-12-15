/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:11:55 by romain            #+#    #+#             */
/*   Updated: 2020/12/15 13:45:05 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "float.h"
#include <wchar.h>

void					write_b(va_list *param, t_pars *pars)
{
	unsigned int	nb;
	long int		tmp;

	if (pars->bw_flags & CROISI && pars->bw_flags & MINUS)
	{
		tmp = va_arg(*param, int);
		nb = -tmp;
		pars->sign = '-';
		pars->print_sign = 1;
		pars->bw_flags &= ~(MINUS);
	}
	else
		nb = va_arg(*param, unsigned int);
	lobby_numeric_converter(nb, "01", pars, 2);
}

unsigned long long int	get_unsigned_param(va_list *param, t_pars *pars)
{
	unsigned long long int	nb;

	if (pars->bw_flags & LLLL)
		nb = va_arg(*param, unsigned long long int);
	else if (pars->bw_flags & LL)
		nb = va_arg(*param, unsigned long int);
	else
		nb = va_arg(*param, unsigned int);
	if (pars->bw_flags & HHHH)
		nb = (unsigned char)nb;
	else if (pars->bw_flags & HH)
		nb = (unsigned short)nb;
	return (nb);
}

int						widestring_len(wchar_t *str, t_pars *pars)
{
	int	i;
	int	j;
	int	jtemp;

	i = -1;
	j = 0;
	while (str[++i])
	{
		jtemp = 0;
		if (str[i] <= 0x7F)
			jtemp = 1;
		else if (str[i] <= 0x7FF)
			jtemp = 2;
		else if (str[i] <= 0xFFFF)
			jtemp = 3;
		else if (str[i] <= 0x10FFFF)
			jtemp = 4;
		if (j + jtemp <= pars->precision_val ||
				!(pars->bw_flags & PRECIS))
			j += jtemp;
		else
			return (j);
	}
	return (j);
}

int						count_trailing_zero(t_doub *doub, int index)
{
	int	i;

	i = 0;
	while (doub->strdoub[index] == '0' && index-- >= doub->point)
		i++;
	return (i);
}

int						check_float_coherence(t_pars *pars, long double doub)
{
	int	inf;

	if (is_not_number(doub))
		pars->str = "nan";
	else if ((inf = is_infinite(doub)) != 0)
	{
		pars->sign = '-';
		if (doub < 0)
			pars->str = "inf";
		else
		{
			pars->str = "inf";
			pars->sign = '+';
		}
	}
	else
		return (0);
	if (pars->bw_flags & ZERO)
		pars->bw_flags &= ~(ZERO);
	pars->precision_val = 0;
	pars->size_str = 3;
	set_comp_num(pars);
	return (1);
}
