/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/23 00:32:14 by romain           ###   ########.fr       */
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
	{NULL, -1}
};

int		lobby_write_buffer(va_list *param, t_flags *flags)
{
	int			i;

	i = -1;
	while (g_tab_function[++i].c != -1)
	{
		if (g_tab_function[i].c == flags->convert_char)
		{
			g_tab_function[i].pt_function(param, flags);
			return (1);
		}
	}
	if (flags->convert_char == '%')
	{
		write_pct(flags);
		return (1);
	}
	return (0);
}
