/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/20 17:05:55 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	write_char_null(t_buffer *buf)
{
	if (buf->pars.boundary_left)
	{
		write_char_buffer(buf, '\0', 1);
		write_char_buffer(buf, ' ', buf->pars.field_width_val - 1);
	}
	else
	{
		write_char_buffer(buf, ' ', buf->pars.field_width_val - 1);
		write_char_buffer(buf, '\0', 1);
	}
}

void	write_string(t_buffer *buf, char *str, char *strnull)
{
	int	sizetoprint;

	if (!str)
		str = strnull;
	sizetoprint = my_strlen(str);
	if (buf->pars.precision_bool && sizetoprint > buf->pars.precision_val)
		sizetoprint = buf->pars.precision_val;
	if (buf->pars.boundary_left)
	{
		write_str_buffer(buf, str, sizetoprint);
		write_char_buffer(buf, ' ', buf->pars.field_width_val - sizetoprint);
	}
	else
	{
		write_char_buffer(buf, ' ', buf->pars.field_width_val - sizetoprint);
		write_str_buffer(buf, str, sizetoprint);
	}
}
