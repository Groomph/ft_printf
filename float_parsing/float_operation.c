/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:03:15 by romain            #+#    #+#             */
/*   Updated: 2020/11/30 20:22:41 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_parsing.h"

int	shift_left_erase(char *str, int i)
{
	str[i] = str[i + 1];
	if (str[i])
		return (shift_left_erase(str, i + 1));
	else
		return (i);
}

int	shift_right_add(char *str, char c, int i)
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
	tmp = str[i];
	str[i] = c;
	return (shift_right_add(str, tmp, i + 1));
}

int	digit_str_rounder(t_doub *doub, int i)
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
