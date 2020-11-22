/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/22 21:52:46 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void		lobby_write_buffer(va_list *param, t_flags *flags)
{
	static t_converter	tab_function[] =
	{
		{&write_c, 'c'},
		{&write_di, 'd'},
		{&write_di, 'i'},
		{&write_p, 'p'},
		{&write_s, 's'},
		{&write_u, 'u'},
		{&write_x, 'x'},
		{&write_X, 'X'},
		{NULL, -1}
	};
	int	i;

	i = -1;
	while (tab_function[++i].c != -1)
	{
		if (tab_function[i].c == flags->convert_char)
		{
			tab_function[i].pt_function(param, flags);	
			return ;
		}
	}
	if (flags->convert_char == '%')
		write_PCT(flags);	
}
