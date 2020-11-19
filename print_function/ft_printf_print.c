/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/20 00:29:39 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		convert_base(unsigned long nb, int sizeb, char *base, t_pars *pars)
{
	char			tmp[80];
	int				i;
	unsigned long	nb2;
	int				size;

	if (nb == 0 && pars->precision_bool && pars->precision_val == 0)
		return (print_unsigned_digit("", 0, pars));
	else if (nb == 0)
		return (print_unsigned_digit("0", 1, pars));
	i = 1;
	nb2 = nb;
	while (nb2 /= sizeb)
		i++;
	size = i;
	tmp[i--] = '\0';
	nb2 = nb;
	while (nb2)
	{
		tmp[i--] = base[nb2 % sizeb];
		nb2 /= sizeb;
	}
	return (print_unsigned_digit(tmp, size, pars));
}

int		my_itoa(int nb, t_pars *pars)
{
	char			tmp[80];
	int				i;
	unsigned int	nb2;
	int				size;

	if (nb >= 0)
		return (convert_base(nb, 10, "0123456789", pars));
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
	return (print_signed_boundary(tmp, size, pars));
}

int		ft_printf_print2(t_pars *pars, va_list *param)
{
	char	c[2];

	if (pars->convert_char == 'p')
		return (print_addr_hexa(va_arg(*param, unsigned long), pars));
	if (pars->convert_char == 'c')
	{
		c[0] = (char)va_arg(*param, int);
		if (c[0] == '\0')
			return (print_char_null(pars));
		c[1] = '\0';
		if (pars->precision_val == 0 && pars->precision_bool)
			pars->precision_val = 1;
		return (print_string(c, pars, ""));
	}
	if (pars->convert_char == '%')
	{
		if (pars->precision_val == 0 && pars->precision_bool)
			pars->precision_val = 1;
		return (print_string("%", pars, ""));
	}
	return (0);
}

int		ft_printf_print(t_pars *pars, va_list *param)
{
	if (pars->convert_char == 's')
		return (print_string(va_arg(*param, char*), pars, "(null)"));
	if (pars->convert_char == 'x')
	{
		return (convert_base(va_arg(*param, unsigned int),
			16, "0123456789abcdef", pars));
	}
	if (pars->convert_char == 'X')
	{
		return (convert_base(va_arg(*param, unsigned int),
			16, "0123456789ABCDEF", pars));
	}
	if (pars->convert_char == 'd' || pars->convert_char == 'i')
		return (my_itoa(va_arg(*param, int), pars));
	if (pars->convert_char == 'u')
	{
		return (convert_base(va_arg(*param, unsigned int),
			10, "0123456789", pars));
	}
	return (ft_printf_print2(pars, param));
}
