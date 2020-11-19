/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez </var/mail/rsanchez>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:37:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/11/19 22:14:53 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
		
int	print_signed_boundary_no(char tab[], int size, t_pars *pars)
{
	int	i;
	int	i2;
	int	maxprint;

	i = 0;
	i2 = 0;
	maxprint = size;
	if (pars->precision_bool && size < pars->precision_val)
	       maxprint = pars->precision_val;
	if (pars->zero_padded && !pars->precision_bool)
	{
		write(1, "-", 1);
		while (i++ + maxprint < pars->field_width_val)
			write(1, "0", 1);
	}
	else
	{
		while (i++ + maxprint < pars->field_width_val)
			write(1, " ", 1);
		write(1, "-", 1);
	}
	i--;
	while (i2++ + size < maxprint)
		write(1, "0", 1);
	write(1, tab, size);
	return (i + i2 + size);
}

int	print_signed_boundary(char tab[], int size, t_pars *pars)
{
	int	i;
	int	maxprint;

	pars->field_width_val--;
	if (!pars->boundary_left)
		return (print_signed_boundary_no(tab, size, pars));
	i = 0;
	maxprint = size < pars->precision_val ? pars->precision_val : size;
	write(1, "-", 1);
	while (i++ + size <  maxprint)
			write(1, "0", 1);
	write(1, tab, size);
	i--;
	while (i++ + size < pars->field_width_val)
	write(1, " ", 1);
	return (i + size);
}

int	print_unsigned_digit_boundary(char *str, int size, t_pars *pars, int maxprint)
{
	int	i;

	i = 0;
	while (i++ + size < maxprint)
		write(1, "0", 1);
	write(1, str, size);
	i--;
	while (i++ + size < pars->field_width_val)
		write(1, " ", 1);
	return (size + i - 1);
}

int	print_unsigned_digit(char *str, int size, t_pars *pars)
{
	int	i;
	int	i2;
	int	maxprint;

	i = 0;
	i2 = 0;
	maxprint = size;
	if (pars->precision_bool && size < pars->precision_val)
		maxprint = pars->precision_val;
/*
	if (pars->precision_bool == 0)              pas sur de l'interet de ces 2 lignes
		pars->precision_val = 1;
*/
	if (pars->boundary_left)
		return (print_unsigned_digit_boundary(str, size, pars, maxprint));
	while (pars->zero_padded && i++ + maxprint < pars->field_width_val)
		write(1, "0", 1);
	while (!pars->zero_padded && i++ + maxprint < pars->field_width_val)
		write(1, " ", 1);
	i--;
	while (i2++ + size < maxprint)
		write(1, "0", 1);
	write(1, str, size);
	return (size + i + i2 - 1);
}
