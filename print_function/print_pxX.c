/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pxX.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/20 00:01:29 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
		
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
	while (i++ + maxprint < pars->field_width_val && pars->boundary_left)
		write(1, " ", 1);
	return (i - 1 + i2 - 1);	
}

void	print_addr_recurs(unsigned long pt)
{
	if (pt)
	{
		print_addr_recurs(pt / 16);
		write(1, &"0123456789abcdef"[pt % 16], 1);
	}
}

int		print_addr_boundary(unsigned long pt, t_pars *pars, int size, int maxprint)
{
	int	i;

	i = 2;
	write(1, "0x", 2);
	while (i++ + size < maxprint)
		write(1, "0", 1);
	i += size - 1;
	print_addr_recurs(pt);
	while (i++ < pars->field_width_val)
		write(1, " ", 1);
	return (i - 1);
}

int		print_addr_zeropadded(unsigned long pt, t_pars *pars, int size)
{
	int	i;

	i = 0;
	write(1, "0x", 2);
	while (size + i++ < pars->field_width_val)
		write(1, "0", 1);
	i += size;	
	print_addr_recurs(pt);
	return (i + 1);
}
int		print_addr(unsigned long pt, t_pars *pars, int size, int maxprint)
{
	int	i;
	i = 0;
	while (maxprint + i++ + 2 < pars->field_width_val)
		write(1, " ", 1);
	i++;
	write(1, "0x", 2);
	while (i++ + size < maxprint + 2)
		write(1, "0", 1);
	i += size;	
	print_addr_recurs(pt);
	return (i - 1);
}

int		print_addr_hexa(unsigned long pt, t_pars *pars)
{
	int	maxprint;
	int	size;
	unsigned long temp;
	
	if (!pt)	
		return (print_add_null(pars));
	temp = pt;
	size = 1;
	while (temp /= 16)
		size++;
	maxprint = size;
	if (pars->precision_bool && size < pars->precision_val)
		maxprint = pars->precision_val;
	if (pars->boundary_left)
		return (print_addr_boundary(pt, pars, size, maxprint));
	else if (pars->zero_padded)
		return (print_addr_zeropadded(pt, pars, size));
	else
		return (print_addr(pt, pars, size, maxprint));
}
