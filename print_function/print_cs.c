/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/19 22:09:48 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	print_char_null_boundary(t_pars *pars, int maxprint)
{
	write(1, "\0", 1);
	while (maxprint++ < pars->field_width_val)
		write(1, " ", 1);
	return (maxprint - 1);
	
}

int	print_char_null(t_pars *pars)
{
	int	maxprint;
	
	maxprint = 1;
	if (pars->precision_bool && maxprint < pars->precision_val)
		maxprint = pars->precision_val;
	if (pars->boundary_left)
		return (print_char_null_boundary(pars, maxprint));
	while (maxprint++ < pars->field_width_val)
		write(1, " ", 1);
	write(1, "\0", 1);
	return (maxprint - 1);
}

int	print_string_boundary(char *str, t_pars *pars, int size)
{
	write(1, str, size);
	while (size++ < pars->field_width_val)
		write(1, " ", 1);
	return (size - 1);
}

int	print_string(char *str, t_pars *pars, char *strnull)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!str)
		str = strnull;
	while (str[size])
		size++;
	if (pars->precision_bool && size > pars->precision_val)
		size = pars->precision_val;
	if (pars->boundary_left)
		return (print_string_boundary(str, pars, size));
	while (pars->zero_padded && i++ + size < pars->field_width_val)
		write(1, "0", 1);
	while (!pars->zero_padded && i++ + size < pars->field_width_val)
		write(1, " ", 1);
	write(1, str, size);
	return (size + i - 1);
}
