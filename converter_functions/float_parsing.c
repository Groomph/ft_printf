/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/27 10:23:59 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	shift_add_digit_str(char *str, char c, int i, int movepoint)
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
	if ((movepoint || str[i] != '.') && str[i] != '-' && str[i] != '+')
	{
		tmp = str[i];
		str[i] = c;
	}
	else
		tmp = c;
	return (shift_add_digit_str(str, tmp, i + 1, movepoint));
}

static int	digit_str_rounder(int *ptsize, char *temp, t_flags *flags)
{
	int	size;
	int	movepoint;

	size = *ptsize - 1;
	movepoint = 0;
	while (size >= 0 && (temp[size] == '9' || temp[size] == '.'))
	{
		if (temp[size] == '9')
			temp[size] = '0';
		size--;
	}
	if (flags->convert_char == 'e' || flags->convert_char == 'E')
		movepoint = 1;
	if (size < 0)
	{
		shift_add_digit_str(temp, '1', 0, movepoint);
		if (flags->convert_char == 'e' || flags->convert_char == 'E')
			return (1);
		else if (flags->convert_char == 'f')
			(*ptsize)++;
	}
	else
		temp[size]++;
	return (0);
}

static int	write_double_decipart(long double *doub, int size, char *temp,
								t_flags *flags)
{
	int	i;
	long long int	intpart;

	i = 0;
	temp[size++] = '.';
	while (i < flags->precision_val)
	{
		*doub *= 10;
		intpart = *doub;
		temp[size + i++] = intpart + '0';
		*doub -= intpart;
	}
	temp[size + i] = '\0';
	return (size + i);
}

int	write_double_regular(long double doub, t_flags *flags, char *temp,
								int *exponent)
{
	long long int	intpart;
	int		size;

	intpart = doub;
	if (!flags->precision_val && ((doub - intpart > 0.5 && intpart % 2 == 0)
			|| (doub - intpart >= 0.5 && intpart % 2 == 1)))
	{
		doub += 0.5;
		intpart = doub;
	}
	size = my_utoa_len(intpart, 10, NULL);
	write_digit_str(intpart, temp, size - 1);
	if (!flags->precision_val)
	{
		if (flags->bw_flags & CROISI)
			temp[size++] = '.';
		temp[size] = '\0';
		return (size);
	}
	doub -= intpart;
	size = write_double_decipart(&doub, size, temp, flags);
	if (doub >= 0.5)
		*exponent += digit_str_rounder(&size, temp, flags);
	return (size);
}

int	write_double_expo(long double doub, t_flags *flags, char *temp,
								int *exponent)
{
	int	size;
	int positiver;

	*exponent = 0;
	positiver = 1;
	while (doub && doub < 1 && --(*exponent))
		doub *= 10;
	while (doub && doub >= 10 && ++(*exponent))
		doub /= 10;
	size = write_double_regular(doub, flags, temp, exponent);
	temp[size++] = 'e';
	if (*exponent < 0)
	{
		temp[size++] = '-';
		positiver = -1;
	}
	else
		temp[size++] = '+';
	temp[size++] = *exponent * positiver / 10 + '0';
	temp[size++] = *exponent * positiver % 10 + '0';
	temp[size] = '\0';
	return (size);
}
