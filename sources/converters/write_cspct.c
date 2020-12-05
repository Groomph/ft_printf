/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cspct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/12/05 07:34:18 by romain           ###   ########.fr       */
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

void	handler_wchart(va_list *param, t_pars *pars, short *size)
{
	wchar_t c;

	c = va_arg(*param, wint_t);
	if (c <= 0x7F)
	{
		*size = 1;
		pars->str[0] = c;
	}
	else if (c <= 0x7FF)
	{
		pars->str[0] = (c >> 6) + 0xC0;
		pars->str[1] = (c & 0x3F) + 0x80;
		*size = 2;
	}
	else if (c <= 0xFFFF)
	{
		pars->str[0] = (c >> 12) + 0xE0;
		pars->str[1] = ((c >> 6) & 0x3F) + 0x80;
		pars->str[2] = (c & 0x3F) + 0x80;
		*size = 3;
	}
	else if (c <= 0x10FFFF)
	{
		pars->str[0] = (c >> 18) + 0xF0;
		pars->str[1] = ((c >> 12) & 0x3F) + 0x80;
		pars->str[2] = ((c >> 6) & 0x3F) + 0x80;
		pars->str[3] = (c & 0x3F) + 0x80;
		*size = 4;
	}
	else
		*size = 0;
}

void		write_c(va_list *param, t_pars *pars)
{
	char		c;
	char		tab[4];

	if (pars->precision_val == 0 && pars->bw_flags & PRECIS)
		pars->precision_val = 1;
	if (pars->bw_flags & LL)
	{
		pars->size_str = 0;
		pars->str = tab;
		handler_wchart(param, pars, &(pars->size_str));
		pars->precision_val = pars->size_str;
//		printf("size char: %d\n", pars->size_str);
	}
	else
	{
		c = (char)va_arg(*param, int);
		pars->str = &c;
		pars->size_str = 1;
	}
	set_comp_cs(pars);
	write_into_buffer(pars);
}

void		write_s(va_list *param, t_pars *pars)
{
	pars->str = va_arg(*param, char*);
	if (!pars->str)
		pars->str = "(null)";
	pars->size_str = string_len(pars->str);
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
