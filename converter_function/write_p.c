/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/20 19:08:53 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void		write_addr_null(t_buffer *buf)
{
	int	maxprint;
	int	space_toprint;
	int	_0_toprint;

	maxprint = 3;
	if (buf->pars.precision_bool)
	       maxprint = buf->pars.precision_val + 2;
	space_toprint = buf->pars.field_width_val - maxprint;
	_0_toprint = maxprint - 2;
	if (!buf->pars.boundary_left)
		write_char_buffer(buf, ' ', space_toprint);
	write_str_buffer(buf, "0x", 2);
	write_char_buffer(buf, '0', _0_toprint);
	if (buf->pars.boundary_left)
		write_char_buffer(buf, ' ', space_toprint);
}

void	write_addr_recurs(t_buffer *buf, unsigned long pt, int i)
{
	if (pt / 16)
		write_addr_recurs(buf, pt / 16, i + 1);
	write_char_buffer(buf, "0123456789abcdef"[pt % 16], 1);
}

void		write_addr_boundary(t_buffer *buf, unsigned long pt, int size)
{
	int	maxprint;
	int	space_toprint;
	int	_0_toprint;

	maxprint = size;
	if (buf->pars.precision_bool && size < buf->pars.precision_val)
		maxprint = buf->pars.precision_val;
	space_toprint = buf->pars.field_width_val - maxprint - 2;
	_0_toprint = maxprint - size - 2;
	write_str_buffer(buf, "0x", 2);
	write_char_buffer(buf, '0', _0_toprint);
	write_addr_recurs(buf, pt, 0);
	write_char_buffer(buf, ' ', space_toprint);
}

void		write_addr_zeropadded(t_buffer *buf, unsigned long pt, int size)
{
	int	_0_toprint;

	write_str_buffer(buf, "0x", 2);
	_0_toprint = buf->pars.field_width_val - size;	
	write_char_buffer(buf, '0', _0_toprint);
	write_addr_recurs(buf, pt, 0);
}

void		write_addr(t_buffer *buf, unsigned long pt, int size)
{
	int maxprint;
	int space_toprint;
	int _0_toprint;
	
	maxprint = size;
	if (buf->pars.precision_bool && size < buf->pars.precision_val)
		maxprint = buf->pars.precision_val;
	space_toprint = buf->pars.field_width_val - maxprint - 2;
	_0_toprint = maxprint - size;
	write_char_buffer(buf, ' ', space_toprint);
	write_str_buffer(buf, "0x", 2);
	write_char_buffer(buf, '0', _0_toprint);
	write_addr_recurs(buf, pt, 0);
}

void		write_addr_hexa(t_buffer *buf, unsigned long pt)
{
	int	size;
	
	if (!pt)	
		return (write_addr_null(buf));
	size = my_utoa_len(pt, 16);
	if (buf->pars.boundary_left)
		write_addr_boundary(buf, pt, size);
	else if (buf->pars.zero_padded)
		write_addr_zeropadded(buf, pt, size);
	else
		write_addr(buf, pt, size);
}
