/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez </var/mail/rsanchez>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:37:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/11/19 17:19:25 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
		
int		print_signed_boundary_no(char tab[], int size, t_pars *pars)
{
	int	i;
	int	i2;
	int	maxprint;

	i = 0;
	i2 = 0;
	maxprint = size < pars->precision_val ? pars->precision_val : size;
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

int		print_signed_boundary(char tab[], int size, t_pars *pars)
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

int		print_unsigned_digit(char *str, int size, t_pars *pars)
{
	int	i;
	int	i2;
	int	maxprint;

	i = 0;
	i2 = 0;
	maxprint = size < pars->precision_val ? pars->precision_val : size;
	if (pars->precision_bool == 0)
		pars->precision_val = 1;
	if (pars->boundary_left)
	{
		while (i++ + size < maxprint)
			write(1, "0", 1);
		write(1, str, size);
		i--;
		while (i++ + size < pars->field_width_val)
			write(1, " ", 1);
		return (size + i - 1);
	}
	while (i++ + maxprint< pars->field_width_val)
		pars->zero_padded && !pars->precision_bool ? write(1, "0", 1): write(1, " ", 1);
	i--;
	while (i2++ + size < maxprint)
		write(1, "0", 1);
	write(1, str, size);
	return (size + i + i2 - 1);
}
