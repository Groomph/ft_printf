/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cspct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:36:44 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:36:52 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>

static void	set_comp_cs(t_pars *pars)
{
	if (pars->bw_flags & PRECIS && pars->size_str > pars->precision_val)
		pars->size_str = pars->precision_val;
	pars->field_width_val -= pars->size_str;
	if (pars->field_width_val)
		fill_width(pars, pars->field_width_val);
}

void		handle_wchar(va_list *param, t_pars *pars)
{
	wchar_t		wchar[2];
	wchar_t		*wstr;

	if (pars->convert_char == 'c')
	{
		wchar[0] = va_arg(*param, wint_t);
		wchar[1] = 0;
		wstr = wchar;
		if (pars->bw_flags & PRECIS)
			pars->precision_val = 4;
		pars->size_str = widestring_len(wstr, pars);
	}
	else
	{
		wstr = va_arg(*param, wchar_t*);
		pars->size_str = widestring_len(wstr, pars);
	}
	set_comp_cs(pars);
	write_into_buffer(pars, wstr);
}

void		write_c(va_list *param, t_pars *pars)
{
	char		c;

	if (pars->precision_val == 0 && pars->bw_flags & PRECIS)
		pars->precision_val = 1;
	pars->size_str = 1;
	if (pars->bw_flags & LL)
		handle_wchar(param, pars);
	else
	{
		c = (char)va_arg(*param, int);
		pars->str = &c;
		set_comp_cs(pars);
		write_into_buffer(pars, 0);
	}
}

void		write_s(va_list *param, t_pars *pars)
{
	if (pars->bw_flags & LL)
		handle_wchar(param, pars);
	else
	{
		pars->str = va_arg(*param, char*);
		if (!pars->str)
			pars->str = "(null)";
		pars->size_str = string_len(pars->str);
		set_comp_cs(pars);
		write_into_buffer(pars, 0);
	}
}

void		write_pct(va_list *param, t_pars *pars)
{
	char	c;

	if (pars->precision_val == 0 && pars->bw_flags & PRECIS)
		pars->precision_val = 1;
	c = '%';
	pars->size_str = 1;
	pars->str = &c;
	if (param)
		set_comp_cs(pars);
	write_into_buffer(pars, 0);
}
