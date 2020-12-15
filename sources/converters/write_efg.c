/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_efg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:37:28 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:37:30 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "float.h"

static void	set_comp_g(t_doub *doub, t_pars *pars)
{
	pars->size_str = doub->size;
	if (pars->size_str > pars->precision_val)
		pars->size_str = pars->precision_val;
	if (!(pars->bw_flags & CROISI))
		pars->size_str -= count_trailing_zero(doub, pars->size_str - 1);
	pars->str[pars->size_str] = '\0';
	if (pars->size_str > doub->point ||
			(pars->size_str == doub->point && pars->bw_flags & CROISI))
	{
		pars->size_str = shift_right_add(pars->str, '.', doub->point);
	}
	add_sign_numeric(pars, doub->sign);
	if (pars->bw_flags & CROISI)
		pars->zero_after = pars->precision_val - doub->size;
	if (pars->zero_after < 0)
		pars->zero_after = 0;
	pars->field_width_val -= (pars->size_str + pars->zero_after);
	if (pars->field_width_val > 0)
		fill_width(pars, pars->field_width_val);
	write_into_buffer(pars, 0);
}

static void	lobby_write_g(t_doub *doub, t_pars *pars, char e_or_f)
{
	char	expo[4];
	int		i;

	if (e_or_f == 'e')
	{
		if (!(doub->isnull))
		{
			write_exponent(doub->exponent, expo);
			pars->field_width_val -= 4;
			pars->extra_after = expo;
			pars->size_extra = 4;
		}
	}
	else
	{
		i = 0;
		while (doub->strdoub[0] == '0' && doub->point == 1
				&& doub->strdoub[i] == '0' && i++ < doub->size)
			pars->precision_val++;
		round_float(doub, pars->precision_val);
	}
	pars->str = doub->strdoub;
	set_comp_g(doub, pars);
}

void		write_g(va_list *param, t_pars *pars)
{
	t_doub	doub;
	t_doub	temp;
	int		preci_zero;

	doub.doub = va_arg(*param, double);
	preci_zero = 0;
	if (check_float_coherence(pars, doub.doub))
		return ;
	if (!(pars->bw_flags & PRECIS))
	{
		pars->bw_flags |= PRECIS;
		pars->precision_val = 6;
	}
	else if (pars->precision_val == 0)
	{
		preci_zero = 1;
		pars->precision_val = 1;
	}
	init_struct_double(&doub);
	temp = find_exponent(doub, pars->precision_val);
	if (temp.exponent >= pars->precision_val || temp.exponent < -4)
		lobby_write_g(&temp, pars, 'e');
	else
		lobby_write_g(&doub, pars, 'f');
}

static void	set_comp_ef(t_doub *doub, t_pars *pars)
{
	int	decisize;

	decisize = doub->size - doub->point;
	pars->str = doub->strdoub;
	pars->size_str = doub->size;
	if (decisize > pars->precision_val)
		pars->size_str = doub->point + pars->precision_val;
	pars->str[pars->size_str] = '\0';
	if (pars->precision_val || pars->bw_flags & CROISI)
		pars->size_str = shift_right_add(pars->str, '.', doub->point);
	add_sign_numeric(pars, doub->sign);
	pars->zero_after = pars->precision_val - decisize;
	if (pars->zero_after < 0)
		pars->zero_after = 0;
	pars->field_width_val -= (pars->size_str + pars->zero_after);
	if (pars->field_width_val > 0)
		fill_width(pars, pars->field_width_val);
}

void		write_ef(va_list *param, t_pars *pars)
{
	t_doub	doub;
	char	expo[4];

	doub.doub = va_arg(*param, double);
	if (check_float_coherence(pars, doub.doub))
		return ;
	if (!(pars->bw_flags & PRECIS))
	{
		pars->bw_flags |= PRECIS;
		pars->precision_val = 6;
	}
	init_struct_double(&doub);
	if (pars->convert_char == 'e')
	{
		pars->field_width_val -= 4;
		doub = find_exponent(doub, pars->precision_val + 1);
		pars->extra_after = expo;
		pars->size_extra = 4;
		write_exponent(doub.exponent, expo);
	}
	else
		round_float(&doub, doub.point + pars->precision_val);
	set_comp_ef(&doub, pars);
	write_into_buffer(pars, 0);
}
