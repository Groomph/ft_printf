/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_efg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:34:27 by romain            #+#    #+#             */
/*   Updated: 2020/12/03 14:51:05 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../float_parsing/float_parsing.h"

static void     set_comp_g(t_doub *doub, t_pars *pars)
{
	pars->size_str = doub->size;
	if (pars->size_str > pars->precision_val)
		pars->size_str = pars->precision_val;
	if (!(pars->bw_flags & CROISI))
		pars->size_str -= count_clean_zero(doub, pars->size_str - 1, 1);
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
}

static void    lobby_write_gE(t_doub *doub, t_pars *pars)
{
	char	expo[4];

	if (!(doub->isnull))
	{
		write_exponent(doub->exponent, expo);
		pars->field_width_val -= 4;
		pars->extra_after = expo;
		pars->size_extra = 4;
	}
	pars->str = doub->strdoub;
	set_comp_g(doub, pars);
	write_into_buffer(pars);
}

void	write_g(va_list *param, t_pars *pars)
{
	t_doub	doub;
	t_doub	temp;

	if (!(pars->bw_flags & PRECIS))
	{
		pars->bw_flags |= PRECIS;
		pars->precision_val = 6;
	}
	else if (pars->precision_val == 0)
		pars->precision_val = 1;
	doub.doub = va_arg(*param, double);	
	init_struct_double(&doub);
	temp = find_exponent(doub, pars->precision_val);
	if (temp.exponent >= pars->precision_val || temp.exponent < -4)
	{
		lobby_write_gE(&temp, pars);
		return ;
	}
	if (doub.strdoub[0] == '0' && doub.point == 1 && doub.strdoub[1])
		pars->precision_val++;
	round_float(&doub, pars->precision_val);
	pars->str = doub.strdoub;
	set_comp_g(&doub, pars);
	write_into_buffer(pars);
}

static void     set_comp_ef(t_doub *doub, t_pars *pars)
{
        int     decisize;

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

void	write_e(va_list *param, t_pars *pars)
{
	t_doub		doub;
	char		expo[4];

	if (!(pars->bw_flags & PRECIS))
        {
	        pars->bw_flags |= PRECIS;
              pars->precision_val = 6;
	}
	pars->field_width_val -= 4;
	doub.doub = va_arg(*param, double);
	init_struct_double(&doub);
	doub = find_exponent(doub, pars->precision_val + 1);
	set_comp_ef(&doub, pars);
	pars->extra_after = expo;
	pars->size_extra = 4;
	write_exponent(doub.exponent, expo);
	write_into_buffer(pars);
}

void    write_f(va_list *param, t_pars *pars)
{
        t_doub          doub;

        if (!(pars->bw_flags & PRECIS))
        {
                pars->bw_flags |= PRECIS;
              pars->precision_val = 6;
        }
        doub.doub = va_arg(*param, double);
        init_struct_double(&doub);
        round_float(&doub, doub.point + pars->precision_val);
        set_comp_ef(&doub, pars);
        write_into_buffer(pars);
}
