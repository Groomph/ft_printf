/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/11/20 17:49:16 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_buffer(t_buffer *buf, int fd)
{
		write(fd, buf->buf, buf->i);
		buf->totalsize += buf->i;
		buf->i = 0;
}

void		write_str_buffer(t_buffer *buf, char *str, int size)
{
	int	i2;

	i2 = 0;
	while (i2 < size)
	{
		buf->buf[buf->i++] = str[i2++];
		if (buf->i == BUFFER_SIZE)
			print_buffer(buf, 1);
	}
}

void		write_char_buffer(t_buffer *buf, char c, int nb)
{
	int	i2;

	i2 = 0;
	while (i2++ < nb)
	{
		buf->buf[buf->i++] = c;
		if (buf->i == BUFFER_SIZE)
			print_buffer(buf, 1);
	}
}	

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	param;
	int		tmp;
	t_buffer	buf;

	i = 0;
	tmp = 0;
	va_start(param, str);
	buf.i = 0;
	buf.totalsize = 0;
	while (str[i])
	{
		if (str[i] == '%')
			tmp = ft_printf_parsing((char*)&str[i], &buf, &param);
		if (tmp == 0)
			write_char_buffer(&buf, str[i++], 1);
		else
		{
			while (str[i] && tmp > 0)
			{
				i++;
				tmp--;
			}
		}
	}
	va_end(param);
	print_buffer(&buf, 1);
	return (buf.totalsize);
}
