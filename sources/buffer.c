/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/12/15 12:46:30 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

static t_buffer	g_buf;

int		print_buffer(int fd)
{
	write(fd, g_buf.bufstr, g_buf.i);
	g_buf.totalsize += g_buf.i;
	g_buf.i = 0;
	return (g_buf.totalsize);
}

void	write_str_buffer(const char *str, int size)
{
	int	i2;

	i2 = 0;
	while (i2 < size)
	{
		g_buf.bufstr[g_buf.i++] = str[i2++];
		if (g_buf.i == BUFFER_SIZE)
			print_buffer(1);
	}
}

void	write_char_buffer(char c, int nb)
{
	int	i2;

	i2 = 0;
	while (i2++ < nb)
	{
		g_buf.bufstr[g_buf.i++] = c;
		if (g_buf.i == BUFFER_SIZE)
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

void	init_buffer(void)
{
	g_buf.i = 0;
	g_buf.totalsize = 0;
}
