/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_efg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:34:27 by romain            #+#    #+#             */
/*   Updated: 2020/12/05 08:42:51 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "float.h"

static int     check_float_coherence(t_pars *pars, long double doub)
{
        int     inf;

        if (is_NaN(doub))
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

static void     set_comp_g(t_doub *doub, t_pars *pars)
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
	write_into_buffer(pars);
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
}

void	write_g(va_list *param, t_pars *pars)
{
	t_doub	doub;
	t_doub	temp;

	doub.doub = va_arg(*param, double);
	if (check_float_coherence(pars, doub.doub))
		return ;
	if (!(pars->bw_flags & PRECIS))
	{
		pars->bw_flags |= PRECIS;
		pars->precision_val = 6;
	}
	else if (pars->precision_val == 0)
		pars->precision_val = 1;
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

void	write_ef(va_list *param, t_pars *pars)
{
	t_doub		doub;
	char		expo[4];

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
	write_into_buffer(pars);
}
