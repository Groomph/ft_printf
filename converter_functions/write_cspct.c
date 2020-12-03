/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cspct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/12/03 13:46:11 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	set_comp_cs(t_pars *pars)
{
	if (pars->bw_flags & PRECIS && pars->size_str > pars->precision_val)
		pars->size_str = pars->precision_val;
	pars->field_width_val -= pars->size_str;
	if (pars->field_width_val)
		fill_width(pars, pars->field_width_val);
}

void		write_c(va_list *param, t_pars *pars)
{
	char		c;

	if (pars->precision_val == 0 && pars->bw_flags & PRECIS)
		pars->precision_val = 1;
	c = (char)va_arg(*param, int);
	pars->str = &c;
	pars->size_str = 1;
	set_comp_cs(pars);
	write_into_buffer(pars);
}

void		write_s(va_list *param, t_pars *pars)
{
	pars->str = va_arg(*param, char*);
	if (!pars->str)
		pars->str = "(null)";
	pars->size_str = my_my_strlen(pars->str);
	set_comp_cs(pars);
	write_into_buffer(pars);
}

void		write_pct(va_list *param, t_pars *pars)
{
	char	c;

	if (pars->precision_val == 0 && pars->bw_flags & PRECIS)
		pars->precision_val = 1;
	c = '%';
	pars->str = &c;
	pars->size_str = 1;
	if (param)
		set_comp_cs(pars);
	write_into_buffer(pars);
}
