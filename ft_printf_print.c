/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/16 17:56:03 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

//char	*my_itoa(int nb);
//char	*tohexa(int nb);

typedef struct	s_pars
{
	int boundary_left;
	int zero_padded;
	int precision_bool;
	int precision_val;
	int field_width_val;
	char convert_char;
	char *todisplay;
}		t_pars;

int	my_strcpy(char *str, t_pars *pars);
/*
static int		my_atoi(char *str, int *i)
{
	unsigned int	nb;
	int		neg;

	neg = 1;
	nb = 0;
	if (str[*i] == '-')
	{
		neg = -1;
		(*i)++;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		nb *= 10;
		nb += str[*i] - '0';
		(*i)++;
	}
	return (nb * neg);
}

char	*my_itoa(int nb)
{
	char		*tmp;
	int		i;
	unsigned int	nb2;
	
	i = nb < 0 ? 2 : 1;
	nb2 = nb < 0 ? -nb : nb;
	while (nb2 /= 10)
		i++;
	if (!(tmp = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	tmp[i--] = '\0';
	nb2 = nb < 0 ? -nb : nb;
	while (nb2)
	{
		tmp[i--] = nb2 % 10 + '0';
		nb2 /= 10;
	}
	if (nb < 0)
		tmp[0] = '-';
	return (tmp);
}
*/
int	print_digit(char *str, int size, t_pars *pars)
{
	int	i;

	i = 0;
	if (str[0] == '0' && str[1] == '\0' && pars->precision_bool && pars->precision_val == '0')
	{
		str[0] = '\0';
		size = 0;
	}
	else if (pars->precision_bool == 0)
		pars->precision_val = 1;
	if (pars->boundary_left)
	{
		while (i++ + size < pars->precision_val)
			write(1, "0", 1);
		write(1 , str, size);
		i--;
		while (i++ + size < pars->field_width_val)
			write(1, " ", 1);
		return (size + i - 1);
	}
	while (i++ < pars->field_width_val - pars->precision_val)
		write(1, " ", 1);
	i = 0;
	while (i++ + size < pars->precision_val)
		write(1, "0", 1);
	write(1 , str, size);
	return (size + i - 1);
}

int	convert_base(unsigned int nb, int sizebase, char *base, t_pars *pars)
{
	char		tmp[80];
	int		i;
	unsigned int	nb2;
	int		size;

	i = nb < 0 ? 2 : 1;
	nb2 = nb < 0 ? -nb : nb;
	while (nb2 /= sizebase)
		i++;
	size = i;
	tmp[i--] = '\0';
	nb2 = nb < 0 ? -nb : nb;
	while (nb2)
	{
		tmp[i--] = base[nb2 % sizebase];
		nb2 /= sizebase;
	}
	if (nb < 0)
		tmp[0] = '-';
	return (print_digit(tmp, size, pars));
}
/*
int	print_null(t_pars *pars, char *strnull)
{
	if (pars->precision_val >= 6)
}
*/
int	print_string(char *str, t_pars *pars)
{
	int	i;
	int	max;
	
	max = 0;
	i = 0;
	if (!str && (pars->precision_val >= 6 || !pars->precision_bool))
		str = &"(null)";
	else if (!str)
		str = &"";
	while (str[max])
		max++;
	if (pars->precision_bool)
		max = max < pars->precision_val ? max : pars->precision_val;
	if (pars->boundary_left)
	{
		write(1 , str, max);
		while (max++ < pars->field_width_val)
			write(1, " ", 1);
		return (max - 1);
	}
	while (i++ + max < pars->field_width_val)
		write(1, " ", 1);
	write(1 , str, max);
	return (max + i - 1);
}

int	convert(t_pars *pars, va_list *param)
{
	//static char	*nullstr = "(null)";
	if (pars->convert_char == 's')
		return (print_string(va_arg(*param, char*), pars));
	if (pars->convert_char == 'x')
		return (convert_base(va_arg(*param, unsigned int), 16, "0123456789abcdef", pars));
	if (pars->convert_char == 'X')
		return (convert_base(va_arg(*param, unsigned int), 16, "0123456789ABCDEF", pars));
	if (pars->convert_char == 'd' || pars->convert_char == 'i')
		return (convert_base(va_arg(*param, int), 10, "0123456789", pars));
	if (pars->convert_char == 'u')
		return (convert_base(va_arg(*param, unsigned int), 10, "0123456789", pars));
	if (pars->convert_char == 'p')
		return (convert_base((long)va_arg(*param, unsigned long), 16, "0123456789abcdef", pars));

	return (0);
}

int		ft_printf_print(t_pars *pars, va_list *param)
{
	return (convert(pars, param));
}

