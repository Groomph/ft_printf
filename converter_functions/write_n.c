/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/26 22:13:10 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>

int		clean_zero(char *str, int *size)
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

void		write_g(va_list *param, t_flags *flags)
{
	long double  doub;
        int     sizetoprint;
        int     isneg;
        char    temp[100];
	int	exponent;
	int	limit;
	int	intpartsize;

	exponent = 0;
        doub = va_arg(*param, double);
        isneg = 0;
        if (doub <= 0.0 && ft_is_signed(doub))
        {
                isneg = 1;
                doub *= -1;
        }
        sizetoprint = write_double_expo(doub, flags, temp, &exponent);
	if (exponent >= flags->precision_val || exponent < -4)
	{
		flags->precision_val--;
		exponent = 0;
        	sizetoprint = write_double_expo(doub, flags, temp, &exponent);
		sizetoprint -= 4;
		if (temp[sizetoprint] == 'e' && exponent != 0)
		{
			clean_zero(temp, &sizetoprint);
			temp[sizetoprint++] = 'e'; 
			temp[sizetoprint++] = exponent < 0 ? '-' : '+';
			temp[sizetoprint++] = "0123456789"[exponent < 0 ? exponent * -1 / 10 : exponent / 10];
			temp[sizetoprint++] = "0123456789"[exponent < 0 ? exponent * -1 % 10 : exponent % 10];
			temp[sizetoprint] = '\0'; 
		}
		else
			clean_zero(temp, &sizetoprint);
	}
	else
	{
		
		intpartsize = my_utoa_len(doub, 10, NULL);
		if (!(flags->bw_flags & PRECIS))
		{	
			flags->bw_flags |= PRECIS;
			flags->precision_val = 6;

		}
		else if (flags->precision_val == 0)
			flags->precision_val = 1;
		if (intpartsize >= flags->precision_val)
		{
			while (intpartsize > flags->precision_val)
			{
				doub /= 10;
				intpartsize--;
			}
			flags->precision_val = 0;
		}
		else if (intpartsize < flags->precision_val)
			flags->precision_val -= intpartsize;
		//write(1, "test\n", 5);	
		//printf("doub: %lld\nprecis: %d\n", (long long int)doub, flags->precision_val);
		//write(1, "test", 4);	
		if ((long long int)doub == 0 && flags->precision_val == 0)
			flags->precision_val = 1;
		sizetoprint = write_double_regular(doub, flags, temp, NULL);
		clean_zero(temp, &sizetoprint);
	}
	if (isneg)
               	write_double_neg(flags, sizetoprint, temp);
        else
               	write_double_pos(flags, sizetoprint, temp);
}





void		write_n(va_list *param, t_flags *flags)
{
	int	*pt;
	
	if (flags)
	{
		pt = va_arg(*param, int*);
		*pt = send_totalsize();
	}
}
