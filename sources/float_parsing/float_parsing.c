/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:03:15 by romain            #+#    #+#             */
/*   Updated: 2020/12/14 22:22:18 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "float.h"

void		write_exponent(int exponent, char *tab)
{
	char	sign;

	sign = '+';
	if (exponent < 0)
	{
		sign = '-';
		exponent *= -1;
	}
	tab[0] = 'e';
	tab[1] = sign;
	tab[2] = exponent / 10 + '0';
	tab[3] = exponent % 10 + '0';
}

t_doub		find_exponent(t_doub doub, int precision)
{
	while (doub.point > 1)
		divide_str_double(&doub);
	while (doub.strdoub[0] == '0' && !doub.isnull)
		multiply_str_double(&doub);
	round_float(&doub, precision);
	if (doub.point > 1)
		divide_str_double(&doub);
	return (doub);
}

static void	init_decimal(t_doub *ptdoub, long double doub)
{
	int				i;
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

void		init_longlong_intpart(t_doub *doub)
{
	int			intpart;
	long double	temp_doub;
	int			i;
	int			j;

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

void		init_struct_double(t_doub *doub)
{
	long long int	intpart;

	doub->sign = '+';
	if (doub->doub <= 0.0 && is_double_signed(doub->doub))
	{
		doub->sign = '-';
		doub->doub *= -1;
	}
	if (doub->doub > 1000000000000000000.0)
		init_longlong_intpart(doub);
	else
	{
		intpart = doub->doub;
		doub->point = utoa_base(intpart, doub->strdoub, "0123456789", 10);
		doub->strdoub[doub->point] = '\0';
		init_decimal(doub, doub->doub - intpart);
	}
	doub->exponent = 0;
	doub->isnull = 0;
	if (doub->doub == 0.0 || doub->doub == -0.0)
		doub->isnull = 1;
}
