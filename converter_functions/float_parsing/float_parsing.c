/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:03:15 by romain            #+#    #+#             */
/*   Updated: 2020/12/01 05:24:30 by romain           ###   ########.fr       */
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

void	init_longlong_intpart(t_doub *ptdoub)
{
	int	intpart;
	long double	temp_doub;
	int		i;
	int		j;

	temp_doub = ptdoub->doub;
	i = 0;
	j = 0;
	while (ptdoub->doub >= 10.0 && ++i)
		ptdoub->doub /= 10;
	ptdoub->strdoub[i + 1] = '\0';
	while (j <= i)
	{
		intpart = ptdoub->doub;
		ptdoub->strdoub[j++] = intpart + '0';
		ptdoub->doub -= intpart;
		if (j <= i)
			ptdoub->doub *= 10;
	}
	ptdoub->point = j;
	ptdoub->strdoub[ptdoub->point] = '\0';
	init_decimal(ptdoub, ptdoub->doub);
	ptdoub->doub = temp_doub;
}

void	init_struct_double(t_doub *ptdoub)
{
	long long int	intpart;

/*	long	l;
	ptdoub->doub *= 3.33333333333;
	l = *(long *)&ptdoub->doub;
	    if (l == 0x7F800000) // +inf
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
    if (l == 0xFF800000) // -inf
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
    if (l == 0x7FFFFFFF) // NaN
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
*/
	ptdoub->sign = '+';
	if (ptdoub->doub <= 0.0 && ft_is_signed(ptdoub->doub))
	{
		ptdoub->sign = '-';
		ptdoub->doub *= -1;
	}
/*
	if (ptdoub->doub <= FLT_MAX)
	{
	       if (ptdoub->doub >= -FLT_MAX)
		write(1, "ok", 0);
		else
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
	}
	else
	{
		if (ptdoub->doub > 0)
		write(1, "inf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10);
	}*/
	if (ptdoub->doub > 1000000000000000000.0)	
		init_longlong_intpart(ptdoub);
	else
	{
		intpart = ptdoub->doub;
		ptdoub->point = my_utoa_len(intpart, 10, NULL);
		write_digit_str(intpart, ptdoub->strdoub, ptdoub->point - 1);
		ptdoub->strdoub[ptdoub->point] = '\0';
		init_decimal(ptdoub, ptdoub->doub - intpart);
	}
	ptdoub->exponent = 0;
	ptdoub->isnull = 0;
	if (ptdoub->doub == 0.0 || ptdoub->doub == -0.0)
		ptdoub->isnull = 1;
}
