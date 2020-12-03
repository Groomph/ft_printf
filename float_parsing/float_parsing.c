/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:03:15 by romain            #+#    #+#             */
/*   Updated: 2020/12/03 09:51:39 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_parsing.h"
#include <float.h>

t_doub	find_exponent(t_doub doub, int precision)
{
	int superior;

	while (doub.point > 1)
		divide_str_double(&doub);
	while (doub.strdoub[0] == '0' && !doub.isnull)
		multiply_str_double(&doub);
	superior = 0;
	if (precision < doub.size - 1)
		superior = is_roundable_bynb(doub, precision);
	if (superior && precision == 1)
	{
 		if ((doub.strdoub[0] % 2 == 0 && superior == 1)
                        || (doub.strdoub[0] % 2 && superior))
                {
			if (digit_str_rounder(&doub, 0))
				divide_str_double(&doub);
		}
	}
	else if (superior)
		if (digit_str_rounder(&doub, precision - 1))
			divide_str_double(&doub);
	return (doub);
}

static void	init_decimal(t_doub *ptdoub, long double doub)
{
	int	i;
	long long int	intpart;
	
	i = 0;
	if (doub == 0.0)
	{
		ptdoub->size = ptdoub->point;
		ptdoub->strdoub[ptdoub->size] = '\0';
		return ;
	}
	while (doub > 0.0 && i + ptdoub->point < 80)
	{
		doub *= 10;
		intpart = doub;
		ptdoub->strdoub[i++ + ptdoub->point] = intpart + '0';
		doub -= intpart;
	}
	ptdoub->strdoub[i + ptdoub->point] = '\0';
	ptdoub->size = i + ptdoub->point;
}

void	init_longlong_intpart(t_doub *doub)
{
	int	intpart;
	long double	temp_doub;
	int		i;
	int		j;

	temp_doub = doub->doub;
	i = 0;
	j = 0;
	while (doub->doub >= 10.0 && ++i)
		doub->doub /= 10;
	doub->strdoub[i + 1] = '\0';
	while (j <= i)
	{
		intpart = doub->doub;
		doub->strdoub[j++] = intpart + '0';
		doub->doub -= intpart;
		if (j <= i)
			doub->doub *= 10;
	}
	doub->point = j;
	doub->strdoub[doub->point] = '\0';
	init_decimal(doub, doub->doub);
	doub->doub = temp_doub;
}

void	init_struct_double(t_doub *doub)
{
	long long int	intpart;

/*	long	l;
	doub->doub *= 3.33333333333;
	l = *(long *)&doub->doub;
	    if (l == 0x7F800000) // +inf
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
    if (l == 0xFF800000) // -inf
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
    if (l == 0x7FFFFFFF) // NaN
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
*/
	doub->sign = '+';
	if (doub->doub <= 0.0 && ft_is_signed(doub->doub))
	{
		doub->sign = '-';
		doub->doub *= -1;
	}
/*
	if (doub->doub <= FLT_MAX)
	{
	       if (doub->doub >= -FLT_MAX)
		write(1, "ok", 0);
		else
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
	}
	else
	{
		if (doub->doub > 0)
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
	}*/
	if (doub->doub > 1000000000000000000.0)	
		init_longlong_intpart(doub);
	else
	{
		intpart = doub->doub;
		doub->point = my_utoa_len(intpart, 10);
		write_digit_str(intpart, doub->strdoub, doub->point - 1);
		doub->strdoub[doub->point] = '\0';
		init_decimal(doub, doub->doub - intpart);
	}
	doub->exponent = 0;
	doub->isnull = 0;
	if (doub->doub == 0.0 || doub->doub == -0.0)
		doub->isnull = 1;
}
