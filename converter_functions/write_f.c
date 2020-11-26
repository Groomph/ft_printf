/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/26 01:33:33 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	write_lobby_double(double doub, t_flags *flags)
{
	long long int	intpart;
	int		limit;
	int		i;
	char		temp[100];
	int		size;

	limit = 6;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	intpart = doub;
	if (!limit && doub - intpart > 0.5 && intpart % 2 == 0)
	{
	//printf("test: %f\n", doub - intpart);
		doub += 0.5;
		intpart = doub;
	}
	else if (!limit && doub - intpart >= 0.5 && intpart % 2 == 1)
	{
	//printf("test: %f\n", doub - intpart);
		doub += 0.5;
		intpart = doub;
	}
	size = my_utoa_len(intpart, 10, NULL);
	write_digit_str(intpart, temp, size - 1);
//	printf("\n%i\n", size);
//	write(1, "\n", 1);
//	write(1, temp, size);
//	write(1, "\n", 1);
	if (!limit)
	{
		write_str_buffer(temp, size);
		return ;
	}
	temp[size++] = '.';
	doub -= intpart;
	i = 0;
	while (i < limit)
	{
		doub *= 10;
		intpart = doub;
		temp[size + i] = intpart + '0';
		doub -= intpart;
		i++;
	}
	if (doub >= 0.5)
	{
		if (digit_str_rounder(temp, i + size - 1))
			write_char_buffer('1', 1);
	}
	write_str_buffer(temp, size + i);
}







static void	write_double_posss(double doub, t_flags *flags, int sizetoprint)
{
	if (flags->bw_flags & MINUS)
	{
		write_lobby_double(doub, flags);
		write_char_buffer(' ', flags->field_width_val - sizetoprint);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', flags->field_width_val - sizetoprint);
		else
			write_char_buffer(' ', flags->field_width_val - sizetoprint);
		write_lobby_double(doub, flags);
	}
}

static void	write_double_neg_nobounddd(double doub, t_flags *flags, int sizetoprint)
{
	int	space_toprint;

	space_toprint = flags->field_width_val - sizetoprint;
	if (flags->bw_flags & ZERO)
	{
		write_char_buffer('-', 1);
		write_char_buffer('0', space_toprint);
	}
	else
	{
		write_char_buffer(' ', space_toprint);
		write_char_buffer('-', 1);
	}
	write_lobby_double(doub, flags);
}

static void	write_double_neggg(double doub, t_flags *flags, int sizetoprint)
{
	int	space_toprint;
	
	if (!(flags->bw_flags & MINUS))
		write_double_neg_nobounddd(doub, flags, sizetoprint);
	else
	{
		space_toprint = flags->field_width_val - sizetoprint;
		write_char_buffer('-', 1);
		write_lobby_double(doub, flags);
		write_char_buffer(' ', space_toprint);
	}
}

void	write_f(va_list *param, t_flags *flags)
{
	//printf("teeeeesssst %X", (unsigned int)-0.0);
	double	doub;
	int	sizetoprint;
	
	doub = va_arg(*param, double);
	//neg = doub < 0 ? 1 : 0;
	//doub = doub < 0 ? -doub : doub;
	sizetoprint = my_utoa_len(doub, 10, NULL);
//	printf("\ntest: %f\n", (-0.0 + 1.2));
	if (flags->bw_flags & PRECIS)
	       	sizetoprint += flags->precision_val == 0 ? 0 : 1 + flags->precision_val;
	else
		sizetoprint += 7;
	if (doub <= 0.0 && ft_is_signed(doub))
		write_double_neggg(-doub, flags, sizetoprint + 1);
	else	
		write_double_posss(doub, flags, sizetoprint);
}
