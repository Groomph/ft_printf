/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/25 23:42:15 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>


int	shift_add_digit_str(char *str, char c, int i)
{
	char	tmp;

	if (!str || !str[i])
	{
		if (!str)
			return (-1);
		str[i] = c;
		str[i + 1] = '\0';
		return (i + 1);
	}
	if (str[i] != '.' && str[i] != '-' && str[i] != '+')
	{
		tmp = str[i];
		str[i] = c;
	}
	else
		tmp = c;
	shift_add_digit_str(str, tmp, i + 1);
}




static int	str_rounder(char *str, int i)
{
	while (i >= 0 && (str[i] == '9' || str[i] == '.'))
	{
		if (str[i] == '9')
			str[i] = '0';
		i--;
	}
	if (i < 0)
		return (1);
	str[i]++;
	return (0);
}

static void write_str(long long int intpart, char *pt, int i)
{
	if (intpart / 10)
		write_str(intpart / 10, pt, i - 1);
	pt[i] = intpart % 10 + '0';
}

static int	write_lobby_double_end(double doub, t_flags *flags, char *temp, int *arrondi)
{
	long long int	intpart;
	int		limit;
	int		i;
	int		size;

	limit = 6;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	intpart = doub;
	if (!limit && doub - intpart > 0.5 && intpart % 2 == 0)
	{
		doub += 0.5;
		intpart = doub;
	}
	else if (!limit && doub - intpart >= 0.5 && intpart % 2 == 1)
	{
		doub += 0.5;
		intpart = doub;
	}
	size = my_utoa_len(intpart, 10, NULL);
	write_str(intpart, temp, size - 1);
	if (!limit)
		return (size) ;
	temp[size++] = '.';
	doub -= intpart;
	i = 0;
	while (i < limit)
	{
		doub *= 10;
		intpart = doub;
		temp[size + i] = intpart + '0';
		doub -= intpart;
		i++;
	}
	if (doub >= 0.5)
	{
		if (str_rounder(temp, i + size - 1))
		{
			shift_add_digit_str(temp, '1', 0);
			(*arrondi)++;
		}
	}
	return (size + i);
}

static int	write_double_expo(double doub, t_flags *flags, char *temp)
{
	int	count;
	int	size;

	count = 0;
	while (doub && doub < 1)
	{	       
		doub *= 10;
		count--;
	}
	while (doub && doub >= 10)
	{       
		doub /= 10;
		count++;
	}
	size = write_lobby_double_end(doub, flags, temp, &count);
	temp[size++] = 'e';
	if (count < 0)
	{
		temp[size++] = '-';
		count *= -1;
	}
	else
		temp[size++] = '+';
	temp[size++] = "0123456789"[count / 10];
	temp[size++] = "0123456789"[count % 10];
	return (size);
}





static void	write_double_pos(t_flags *flags, int sizetoprint, char *temp)
{
	if (flags->bw_flags & MINUS)
	{
		write_str_buffer(temp, sizetoprint);
		write_char_buffer(' ', flags->field_width_val - sizetoprint);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', flags->field_width_val - sizetoprint);
		else
			write_char_buffer(' ', flags->field_width_val - sizetoprint);
		write_str_buffer(temp, sizetoprint);
	}
}

static void	write_double_neg_nobound(t_flags *flags, int sizetoprint, char *temp)
{
	int	space_toprint;

	space_toprint = flags->field_width_val - sizetoprint - 1;
	if (flags->bw_flags & ZERO)
	{
		write_char_buffer('-', 1);
		write_char_buffer('0', space_toprint);
	}
	else
	{
		write_char_buffer(' ', space_toprint);
		write_char_buffer('-', 1);
	}
	write_str_buffer(temp, sizetoprint);
}

static void	write_double_neg(t_flags *flags, int sizetoprint, char *temp)
{
	int	space_toprint;
	
	if (!(flags->bw_flags & MINUS))
		write_double_neg_nobound(flags, sizetoprint, temp);
	else
	{
		space_toprint = flags->field_width_val - sizetoprint - 1;
		write_char_buffer('-', 1);
		write_str_buffer(temp, sizetoprint);
		write_char_buffer(' ', space_toprint);
	}
}

static int        ft_signbit_f(long double x)
{
    return ((1.0 / x) != (1.0 / (x < 0 ? 1 : 0)));
}

void	write_e(va_list *param, t_flags *flags)
{
	double	doub;
	int	sizetoprint;
	int	isneg;
	char	temp[100];

	doub = va_arg(*param, double);
	isneg = 0;
	if (doub <= 0.0 && ft_signbit_f(doub))
	{
		isneg = 1;
		doub *= -1;
	}		
	sizetoprint = write_double_expo(doub, flags, temp);
	if (isneg)
		write_double_neg(flags, sizetoprint, temp);
	else	
		write_double_pos(flags, sizetoprint, temp);
}
