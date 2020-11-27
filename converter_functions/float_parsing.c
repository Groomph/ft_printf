/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/27 03:58:44 by romain           ###   ########.fr       */
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

static int	digit_str_rounder(char *str, int i)
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

static int	write_double_decipart(long double doub, int *limit, char *temp,
								int *exponent)
{
	int	i;
	int	size;
	int	intpart;

	i = 0;
	size = limit[0];
	while (i < limit[1])
	{
		doub *= 10;
		intpart = doub;
		temp[size + i++] = intpart + '0';
		doub -= intpart;
	}
	temp[size + i] = '\0';
	if (doub >= 0.5 && digit_str_rounder(temp, i + size - 1))
	{
		shift_add_digit_str(temp, '1', 0, exponent ? 0 : 1);
		if (exponent)
			(*exponent)++;
		else
			size++;
	}
	return (size + i);
}

int	write_double_regular(long double doub, t_flags *flags, char *temp,
								int *exponent)
{
	long long int	intpart;
	int		size_limit[2];

	size_limit[1] = 6;
	if (flags->bw_flags & PRECIS)
		size_limit[1] = flags->precision_val;
	intpart = doub;
	if (!size_limit[1] && ((doub - intpart > 0.5 && intpart % 2 == 0) ||
			       (doub - intpart >= 0.5 && intpart % 2 == 1)))
	{
		doub += 0.5;
		intpart = doub;
	}
	size_limit[0] = my_utoa_len(intpart, 10, NULL);
	write_digit_str(intpart, temp, size_limit[0] - 1);
	if (!size_limit[1])
	{
		temp[size_limit[0]] = '\0';
		return (size_limit[0]);
	}
	temp[size_limit[0]++] = '.';
	doub -= intpart;
	return (write_double_decipart(doub, size_limit, temp, exponent));
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
