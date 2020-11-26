/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/26 01:56:43 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	shift_add_digit_str(char *str, char c, int i)
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
	return (shift_add_digit_str(str, tmp, i + 1));
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

int	write_double_regular(long double doub, t_flags *flags, char *temp, int *arrondi)
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
	write_digit_str(intpart, temp, size - 1);
	if (!limit)
		return (size);
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
		if (digit_str_rounder(temp, i + size - 1))
		{
			shift_add_digit_str(temp, '1', 0);
			(*arrondi)++;
		}
	}
	return (size + i);
}

int	write_double_expo(long double doub, t_flags *flags, char *temp)
{
	int	count;
	int	size;

	count = 0;
	while (doub && doub < 1)    //count into condition
	{	       
		doub *= 10;
		count--;
	}
	while (doub && doub >= 10)
	{       
		doub /= 10;
		count++;
	}
	size = write_double_regular(doub, flags, temp, &count);
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
