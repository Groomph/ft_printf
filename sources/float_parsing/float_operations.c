/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:35:02 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:35:04 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "float.h"

void	divide_str_double(t_doub *doub)
{
	if (doub->point == 1)
	{
		shift_right_add(doub->strdoub, '0', 0);
		doub->size++;
	}
	else if (doub->point == doub->size &&
			doub->strdoub[doub->size - 1] == '0')
	{
		doub->strdoub[--doub->size] = '\0';
		doub->point--;
	}
	else
		doub->point--;
	doub->exponent++;
	doub->doub /= 10;
}

void	multiply_str_double(t_doub *doub)
{
	if (doub->point == 1 && doub->strdoub[0] == '0')
	{
		shift_left_erase(doub->strdoub, 0);
		doub->size--;
	}
	else if (doub->point == doub->size)
	{
		doub->strdoub[doub->size++] = '0';
		doub->strdoub[doub->size] = '\0';
		doub->point++;
	}
	else
		doub->point++;
	doub->exponent--;
	doub->doub *= 10;
}

int		digit_str_rounder(t_doub *doub, int i)
{
	while (i >= 0 && doub->strdoub[i] == '9')
		doub->strdoub[i--] = '0';
	if (i < 0)
	{
		shift_right_add(doub->strdoub, '1', 0);
		doub->size++;
		doub->point++;
		return (1);
	}
	doub->strdoub[i]++;
	return (0);
}

int		is_roundable_bynb(t_doub doub, int index)
{
	int				i;
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

void	round_float(t_doub *doub, int index)
{
	int	superior;

	superior = 0;
	if (doub->size - 1 >= index)
		superior = is_roundable_bynb(*doub, index);
	if (superior && index <= doub->point)
	{
		if ((doub->strdoub[index - 1] % 2 == 0 && superior == 1)
			|| doub->strdoub[doub->point - 1] % 2)
			digit_str_rounder(doub, index - 1);
	}
	else if (superior)
		digit_str_rounder(doub, index - 1);
}
