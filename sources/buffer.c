/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/12/06 07:54:32 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

static t_buffer	buf;

void		print_buffer(int fd)
{
	write(fd, buf.bufstr, buf.i);
	buf.totalsize += buf.i;
	buf.i = 0;
}

void		write_str_buffer(const char *str, int size)
{
	int	i2;

	i2 = 0;
	while (i2 < size)
	{
		buf.bufstr[buf.i++] = str[i2++];
		if (buf.i == BUFFER_SIZE)
			print_buffer(1);
	}
}

void		write_char_buffer(char c, int nb)
{
	int	i2;

	i2 = 0;
	while (i2++ < nb)
	{
		buf.bufstr[buf.i++] = c;
		if (buf.i == BUFFER_SIZE)
			print_buffer(1);
	}
}

int		write_widechar_buffer(wchar_t c, int size)
{
	if (size-- > 0 && c <= 0x7F)
		write_char_buffer(c, 1); 
	else if (size-- > 0 && c <= 0x7FF)
	{
		write_char_buffer((c >> 6) + 0xC0, 1); 
		write_char_buffer((c & 0x3F) + 0x80, 1); 
	}
	else if (size-- > 0 && c <= 0xFFFF)
	{
		write_char_buffer((c >> 12) + 0xE0, 1); 
		write_char_buffer(((c >> 6) & 0x3F) + 0x80, 1); 
		write_char_buffer((c & 0x3F) + 0x80, 1); 
	}
	else if (size-- > 0 && c <= 0x10FFFF)
	{
		write_char_buffer((c >> 18) + 0xF0, 1); 
		write_char_buffer(((c >> 12) & 0x3F) + 0x80, 1); 
		write_char_buffer(((c >> 6) & 0x3F) + 0x80, 1); 
		write_char_buffer((c & 0x3F) + 0x80, 1); 
	}
	return (size);
}

int		send_totalsize(void)
{
	return (buf.totalsize + buf.i);
}

void	init_buffer(void)
{
	buf.i = 0;
	buf.totalsize = 0;
}
