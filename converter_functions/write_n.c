/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_gn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/29 20:08:01 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
/*
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
	int	intpart_size;
	int	size_toprint;
	
	intpart_size = my_utoa_len(doub, 10, NULL);
	if (flags->precision_val == 0)
		flags->precision_val = 1;
	if (intpart_size >= flags->precision_val)
	{
		while (intpart_size > flags->precision_val)
		{
			doub /= 10;
			intpart_size--;
		}
		flags->precision_val = 0;
	}
	else if (intpart_size < flags->precision_val)
		flags->precision_val -= intpart_size;
	if ((long long int)doub == 0)// && flags->precision_val == 0)
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
	if (exponent != 0)//&& temp[sizetoprint] == 'e')
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
	long double	doubtemp;
	int     size_toprint;
        char    temp[100];
	int	exponent;

        doub = va_arg(*param, double);
        doubtemp = doub;
        if (doub <= 0.0 && ft_is_signed(doub))
        	doubtemp = -doub;
	size_toprint = write_double_expo(doubtemp, flags, temp, &exponent);
	if (!(flags->bw_flags & PRECIS))
	{	
		flags->bw_flags |= PRECIS;
		flags->precision_val = 6;
	}
	if (exponent >= flags->precision_val || exponent < -4)
		size_toprint = redo_write_expo(doubtemp, temp, flags);
	else
		size_toprint = redo_write_regular(doubtemp, temp, flags);
        if (doub <= 0.0 && ft_is_signed(doub))
               	write_double_neg(flags, size_toprint, temp);
        else
               	write_double_pos(flags, size_toprint, temp);
}
*/
void		write_n(va_list *param, t_flags *flags)
{
	int	*pt;
	
	if (flags)
	{
		pt = va_arg(*param, int*);
		*pt = send_totalsize();
	}
}
