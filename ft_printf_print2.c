/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/19 15:24:51 by rsanchez         ###   ########.fr       */
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

int		print_string(char *str, t_pars *pars, char *strnull)
{
	int	i;
	int	max;

	max = 0;
	i = 0;
	if (!str)
		str = strnull;
	while (str[max])
		max++;
	if (pars->precision_bool)
		max = max < pars->precision_val ? max : pars->precision_val;
	if (pars->boundary_left)
	{
		write(1, str, max);
		while (max++ < pars->field_width_val)
			write(1, " ", 1);
		return (max - 1);
	}
	while (i++ + max < pars->field_width_val)
		pars->zero_padded ? write(1, "0", 1): write(1, " ", 1);
	write(1, str, max);
	return (max + i - 1);
}

int		print_add_null(t_pars *pars)
{
	int	maxprint;
	int	i;
	int i2;

	maxprint = pars->precision_bool ? pars->precision_val + 2 : 3;
	i = 0;
	i2 = 2;
	while (i++ + maxprint < pars->field_width_val && !pars->boundary_left)
		write(1, " ", 1);
	i--;
	write(1, "0x", 2);
	while (i2++ < maxprint)
		write(1 , "0", 1);
	if (pars)
	while (i++ < pars->field_width_val && pars->boundary_left)
		write(1, " ", 1);
	return (i - 1 + i2 - 1);	
}

int		print_addr_boundary(unsigned long pt, int i, t_pars *pars)
{
	int	maxprint;
	int	i2;

	i2 = 0;
	if (i == 1)
	{
		maxprint = 9 < pars->precision_val ? pars->precision_val : 9;
		write(1, "0x", 2);
		while (i2++ < maxprint - 9)
			write(1, "0", 1);
		i2 += 9;
	}
	if (i < 9)
		(print_addr_boundary(pt / 16, i + 1, pars));
	write(1, &"0123456789abcdef"[pt % 16], 1);
	while (i == 1 && i2++ + 2 <= pars->field_width_val)
		write(1, " ", 1);
	return (i2);
}

int		print_addr_hexa(unsigned long pt, int i2, int i, t_pars *pars)
{
	int	maxprint;
	
	if (i == 1 && !pt)	
		return (print_add_null(pars));
	else if (pars->boundary_left)
		return (print_addr_boundary(pt, i, pars));
	else if (i == 1)
	{
		pars->zero_padded ? write(1, "0x", 2) : write(1, "", 0);
		maxprint = 9 < pars->precision_val ?	pars->precision_val : 9;
		while (maxprint + i2++ + 2 < pars->field_width_val)
			pars->zero_padded ? write(1, "0", 1) : write(1, " ", 1);
		i2--;
		pars->zero_padded ? write(1, "", 0) : write(1, "0x", 2);
		while (i2++ < maxprint - 9)
			write(1, "0", 1);
		i2 += 9;
	}
	if (i < 9)
		(print_addr_hexa(pt / 16, 0, i + 1, pars));
	write(1, &"0123456789abcdef"[pt % 16], 1);
	while (i == 1 && i2++ + 9 < pars->field_width_val)
		write(1, " ", 1);
	return (i2 += pars->boundary_left ? 9 : 0);
}
