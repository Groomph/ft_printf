/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/20 19:16:21 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void		convert_base(t_buffer *buf, unsigned long nb, int sizeb, char *base)
{
	char			tmp[80];
	int				i;
	unsigned long	nb2;
	int				size;

	if (nb == 0 && buf->pars.precision_bool && buf->pars.precision_val == 0)
		return (write_unsigned_digit(buf, "", 0));
	else if (nb == 0)
		return (write_unsigned_digit(buf, "0", 1));
	i = my_utoa_len(nb, sizeb);
	size = i;
	tmp[i--] = '\0';
	nb2 = nb;
	while (nb2)
	{
		tmp[i--] = base[nb2 % sizeb];
		nb2 /= sizeb;
	}
	write_unsigned_digit(buf, tmp, size);
}

void		my_itoa(t_buffer *buf, int nb)
{
	char			tmp[80];
	int				i;
	unsigned int	nb2;
	int				size;

	if (nb >= 0)
		return (convert_base(buf, nb, 10, "0123456789"));
	i = 1;
	nb2 = nb * -1;
	while (nb2 /= 10)
		i++;
	size = i;
	tmp[i--] = '\0';
	nb2 = nb * -1;
	while (nb2)
	{
		tmp[i--] = nb2 % 10 + '0';
		nb2 /= 10;
	}
	write_signed_boundary(buf, tmp, size);
}

void		ft_printf_print2(t_buffer *buf, va_list *param)
{
	char	c[2];

	if (buf->pars.convert_char == 'p')
		write_addr_hexa(buf, va_arg(*param, unsigned long));
	else if (buf->pars.convert_char == 'c')
	{
		c[0] = (char)va_arg(*param, int);
		if (c[0] == '\0')
			return (write_char_null(buf));
		c[1] = '\0';
		if (buf->pars.precision_val == 0 && buf->pars.precision_bool)
			buf->pars.precision_val = 1;
		write_string(buf, c, "");
	}
	else if (buf->pars.convert_char == '%')
	{
		if (buf->pars.precision_val == 0 && buf->pars.precision_bool)
			buf->pars.precision_val = 1;
		write_string(buf, "%", "");
	}
}

void		ft_printf_print(t_buffer *buf, va_list *param)
{
	if (buf->pars.convert_char == 's')
		write_string(buf, va_arg(*param, char*), "(null)");
	else if (buf->pars.convert_char == 'x')
	{
		convert_base(buf, va_arg(*param, unsigned int),
			16, "0123456789abcdef");
	}
	else if (buf->pars.convert_char == 'X')
	{
		convert_base(buf, va_arg(*param, unsigned int),
			16, "0123456789ABCDEF");
	}
	else if (buf->pars.convert_char == 'd' || buf->pars.convert_char == 'i')
		my_itoa(buf, va_arg(*param, int));
	else if (buf->pars.convert_char == 'u')
	{
		convert_base(buf, va_arg(*param, unsigned int),
			10, "0123456789");
	}
	ft_printf_print2(buf, param);
}
