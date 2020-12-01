/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:12:29 by romain            #+#    #+#             */
/*   Updated: 2020/12/01 11:12:48 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_parsing.h"

void    write_exponent(int exponent)
{
        char    sign;

        sign = '+';
        if (exponent < 0)
        {
                sign = '-';
                exponent *= -1;
        }
        write_char_buffer('e', 1);
        write_char_buffer(sign, 1);
        write_char_buffer(exponent / 10 + '0', 1);
        write_char_buffer(exponent % 10 + '0', 1);
}

int	count_clean_zero(t_doub *doub, int index, int count_clean)
{
	int	i;

	i = 0;
	if (count_clean == 1)
	{
		while (doub->strdoub[index] == '0' && index-- >= doub->point)
			i++;
		return (i);
	}
}

void	round_float(t_doub *doub, int index)
{
	int     superior;

	superior = 0;
	if (doub->size - 1 > index)
		superior = is_roundable_bynb(*doub, index);
	if (superior && index <= doub->point)
	{
		if ((doub->strdoub[index - 1] % 2 == 0 && superior == 1)
				|| (doub->strdoub[doub->point -1] % 2 && superior))
			digit_str_rounder(doub, index - 1);
	}
	else if (superior)
		digit_str_rounder(doub, index - 1);
}

int	is_roundable_bynb(t_doub doub, int index)
{
	int	i;
	long long int	intpart;

	i = 0;
	if (index < doub.point)
	{
		index = doub.point - index;       
		while (i++ < index)
			divide_str_double(&doub);
	}
	if (index > doub.point)
	{
		index -= doub.point;
		while (i++ < index)
			multiply_str_double(&doub);	
	}
	intpart = doub.doub;
	doub.doub -= intpart;
	if (doub.doub > 0.5)
		return (1);
	if (doub.doub >= 0.5)
		return (2);
	return (0);
}
