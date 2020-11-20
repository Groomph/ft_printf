/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_iduxX.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez </var/mail/rsanchez>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:37:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/11/20 17:17:10 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
		
void	write_signed_boundary_no(t_buffer *buf, char tab[], int size)
{
	int	maxprint;
	int	_0_toprint;
	int	space_toprint;

	maxprint = size;
	if (buf->pars.precision_bool && size < buf->pars.precision_val)
	       maxprint = buf->pars.precision_val;
	_0_toprint = maxprint - size;
	space_toprint = buf->pars.field_width_val - maxprint;
	if (buf->pars.zero_padded && !buf->pars.precision_bool)
	{
		write_char_buffer(buf, '-', 1);
		write_char_buffer(buf, '0', buf->pars.field_width_val - size);
	}
	else
	{
		write_char_buffer(buf, ' ', space_toprint);
		write_char_buffer(buf, '-', 1);
	}
	write_char_buffer(buf, '0', _0_toprint);
	write_str_buffer(buf, tab, size);
}

void	write_signed_boundary(t_buffer *buf, char tab[], int size)
{
	int	maxprint;
	int	_0_toprint;
	int	space_toprint;

	if (!buf->pars.boundary_left)
		return (write_signed_boundary_no(buf, tab, size));
	maxprint = size;
	if (buf->pars.precision_val)
		maxprint = buf->pars.precision_val;
	_0_toprint = maxprint - size;
	space_toprint = buf->pars.field_width_val - maxprint;
	write_char_buffer(buf, '-', 1);
	write_char_buffer(buf, '0', _0_toprint);
	write_str_buffer(buf, tab, size);
	write_char_buffer(buf, ' ', space_toprint);
}

void	write_unsigned_boundary(t_buffer *buf, char *str, int size)
{
	int	maxprint;
	int	_0_toprint;
	int	space_toprint;

	maxprint = size;
	if (buf->pars.precision_bool && size < buf->pars.precision_val)
		maxprint = buf->pars.precision_val;
	_0_toprint = maxprint - size;
	space_toprint = buf->pars.field_width_val - maxprint;
	write_char_buffer(buf, '0', _0_toprint);
	write_str_buffer(buf, str, size);
	write_char_buffer(buf, ' ', space_toprint);
}

void	write_unsigned_digit(t_buffer *buf, char *str, int size)
{
	int	maxprint;
	int	_0_toprint;
	int	space_toprint;
	
	if (buf->pars.boundary_left)
		return (write_unsigned_boundary(buf, str, size));
	maxprint = size;
	if (buf->pars.precision_bool && size < buf->pars.precision_val)
		maxprint = buf->pars.precision_val;
	if (!buf->pars.precision_bool && buf->pars.zero_padded)
		_0_toprint = buf->pars.field_width_val - maxprint;
	else
		_0_toprint = maxprint - size;
	space_toprint = buf->pars.field_width_val - maxprint;
	write_char_buffer(buf, ' ', space_toprint);
	write_char_buffer(buf, '0', _0_toprint);
	write_str_buffer(buf, str, size);
}
