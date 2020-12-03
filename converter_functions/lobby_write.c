/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/12/03 07:17:53 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static t_converter	g_tab_function[] =
{
	{&write_c, 'c'},
	{&write_di, 'd'},
	{&write_di, 'i'},
	{&write_o, 'o'},
	{&write_p, 'p'},
	{&write_s, 's'},
	{&write_u, 'u'},
	{&write_x, 'x'},
	{&write_xx, 'X'},
	{&write_n, 'n'},
	{&write_e, 'e'},
	{&write_f, 'f'},
	{&write_g, 'g'},
	{&write_pct, '%'},
	{NULL, -1}
};

void    write_into_buffer(t_pars *pars)
{           
        write_char_buffer(' ', pars->space_before);
	if (pars->extra_before)
        	write_str_buffer(pars->extra_before, pars->size_extra);
        if (pars->sign && pars->print_sign)
                write_char_buffer(pars->sign, 1); 
        write_char_buffer('0', pars->zero_before);
        write_str_buffer(pars->str, pars->size_str);
        write_char_buffer('0', pars->zero_after);
	if (pars->extra_after)
        	write_str_buffer(pars->extra_after, pars->size_extra);
        write_char_buffer(' ', pars->space_after);
}

int		lobby_write_buffer(va_list *param, t_pars *pars)
{
	int			i;

	i = -1;
	while (g_tab_function[++i].c != -1)
	{
		if (g_tab_function[i].c == pars->convert_char)
		{
			g_tab_function[i].pt_function(param, pars);
			return (1);
		}
	}
	return (0);
}
