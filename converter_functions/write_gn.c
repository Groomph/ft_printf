/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_gn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/27 04:07:48 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	clean_zero(char *str, int *size)
{
	while (--*size >= 0 && str[*size] == '0')
	{
		str[*size] = '\0';
	}
	if (str[*size] != '.')
	{
		(*size)++;
		return (1);
	}

	return (0);
}

static int	redo_write_regular(long double doub, char *temp, t_flags *flags)
{
	long long int	intpart;
	int	size_toprint;
	
	intpart = my_utoa_len(doub, 10, NULL);
	if (flags->precision_val == 0)
		flags->precision_val = 1;
	if (intpart >= flags->precision_val)
	{
		while (intpart > flags->precision_val)
		{
			doub /= 10;
			intpart--;
		}
		flags->precision_val = 0;
	}
	else if (intpart < flags->precision_val)
		flags->precision_val -= intpart;
	intpart = doub;
	if (intpart == 0)// && flags->precision_val == 0)
		flags->precision_val += 1;
	size_toprint = write_double_regular(doub, flags, temp, NULL);
	clean_zero(temp, &size_toprint);
	return (size_toprint);
}

static int	redo_write_expo(long double doub, char *temp, t_flags *flags)
{
	int	exponent;
	int	size_toprint;

	flags->precision_val--;
        size_toprint = write_double_expo(doub, flags, temp, &exponent);
	size_toprint -= 4;
	if (/*temp[sizetoprint] == 'e' &&*/ exponent != 0)
	{
		clean_zero(temp, &size_toprint);
		temp[size_toprint++] = 'e'; 
		temp[size_toprint++] = exponent < 0 ? '-' : '+';
		if (exponent < 0)
			exponent = -exponent;
		temp[size_toprint++] = exponent / 10 + '0';
		temp[size_toprint++] = exponent % 10 + '0';
		temp[size_toprint] = '\0'; 
	}
	else
		clean_zero(temp, &size_toprint);
	return (size_toprint);
}

void		write_g(va_list *param, t_flags *flags)
{
	long double  doub;
	int	positiv;
	int     size_toprint;
        char    temp[100];
	int	exponent;

        doub = va_arg(*param, double);
        positiv = 1;
        if (doub <= 0.0 && ft_is_signed(doub))
        	positiv = -1;
	write_double_expo(doub * positiv, flags, temp, &exponent);
	if (!(flags->bw_flags & PRECIS))
	{	
		flags->bw_flags |= PRECIS;
		flags->precision_val = 6;
	}
	if (exponent >= flags->precision_val || exponent < -4)
		size_toprint = redo_write_expo(doub * positiv, temp, flags);
	else
		size_toprint = redo_write_regular(doub * positiv, temp, flags);
        if (positiv == -1)
               	write_double_neg(flags, size_toprint, temp);
        else
               	write_double_pos(flags, size_toprint, temp);
}

void		write_n(va_list *param, t_flags *flags)
{
	int	*pt;
	
	pt = NULL;
	pt = va_arg(*param, int*);
	if (pt && flags)
		*pt = send_totalsize();
}
