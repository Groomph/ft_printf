/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:58:57 by romain            #+#    #+#             */
/*   Updated: 2020/11/25 00:48:20 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>
/*
void	write_lobby_double(double doub, t_flags *flags)
{
	long long int	intpart;
	int			i;
	int			limit;

	i = -1;
	limit = 6;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	if (limit == 0)
		doub += 0.5;
	intpart = doub;
	write_base_recurs(intpart, "0123456789", 10, 50);
	if (limit == 0)
		return ;
	write_char_buffer('.', 1);
	doub -= intpart;
	intpart = 1;
	while (++i < limit)
		intpart *= 10;
	doub *= intpart;
	doub += 0.50;
	intpart = doub;
	write_base_recurs(intpart, "0123456789", 10, limit);
}
*/
/*
void	write_decimal(double doub, int limit)
{
	double multi;
	int	intpart;
	
	multi = 10.0;
	doub *= multi;
	if (1 == limit && (long)doub > 14)
		doub += 1.0;
	intpart = doub;
		write_char_buffer("0123456789"[intpart % 10], 1);
	if (limit > 1)
		write_decimal(doub - multi, limit - 1);
}


void	write_lobby_double(double doub, t_flags *flags)
{
	long int	intpart;
	int			limit;
	double		tmp;

	limit = 6;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	if (limit == 0)
		doub += 0.5;
	intpart = (long int)doub;
	write_base_recurs(intpart, "0123456789", 10, 50);
	if (limit == 0)
		return ;
	write_char_buffer('.', 1);
	tmp = (double)intpart;
	doub -= tmp;
	doub += 1.0;
	printf("test:   %f", doub);
	write_decimal(doub, limit);
}
*/

 /*
void	write_lobby_double(double n, t_flags *flags)
{
	double		decimal;
	long		value;
	int		limit;
	double		multi;
	int	i;
	long	intpart;

	intpart = n;
	write_base_recurs(intpart, "0123456789", 10, 50);
	n -= intpart;
	write_char_buffer('.', 1);
	i = 0;
	multi = 1.0;
	limit = 6;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	while (i++ < limit)
		multi *= 10;
	i = 0;
	decimal = ((n < 0.0f) ? -n : n);
	decimal = decimal * multi;
	decimal = ((long)decimal % 10 > 4) ? (decimal) / 10 + 1 : decimal / 10;
	value = (int)decimal;
	
	write_base_recurs(value, "0123456789", 10, limit);
	while (i < limit)
	{
		write_char_buffer("0123456789"[value % 10], 1);
		value /= 10;
		i++;
	}



}*/
/*
void	write_base(char* pc, char *base, int sizeb, int limit)
{
	char nb;
	char tab[4];
	int	i;
	nb = *pc;
	i = 0;
	while (i < 4)
	{
		tab[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	write_char_buffer(tab[0], 1);
	write_char_buffer(tab[1], 1);
	write_char_buffer(tab[2], 1);
	write_char_buffer(tab[3], 1);
}

void write_lobby_double(double doub, t_flags *flags)
{
	void	*p;
	char	*pc;
	int	i;

	i = 0;
	p = (void*)&doub;
	pc = (char*)p;
	while (i < sizeof(doub) / sizeof(char))
	{
		write_char_buffer('\n', 1);
		write_base(pc, "0123456789", 10, 0);
		write_char_buffer('\n', 1);
		i++;
		p++;
	}

}
*/

/*




static void		ldtoa_fill(double n, long value)
{
	int		len;
	int		accuracy;
	char	s[48];

	len = p->printed - 1 - p->precision;
	accuracy = p->printed - 1 - len;
	while (accuracy--)
	{
		s[len + accuracy + 1] = value % 10 + '0';
		value /= 10;
	}
	(p->precision > 0) ? s[len] = '.' : 0;
	value = (long)(ABS(n));
	while (++accuracy < len)
	{
		s[len - accuracy - 1] = value % 10 + '0';
		value /= 10;
	}
	(p->f & F_APP_PRECI && p->f & F_ZERO) ? s[0] = ' ' : 0;
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
	buffer(p, s, len + 1 + 6);
}

void			pf_putdouble(t_printf *p)
{
	double		n;
	long		tmp;
	int			len;
	double		decimal;
	long		value;

	n = (double)va_arg(p->ap, double);
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	if (!(p->f & F_APP_PRECI))
		p->precision = 6;
	len = (p->precision > 0) ? 1 : 0;
	tmp = (long)(ABS(n));
	while (tmp && ++len)
		tmp /= 10;
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	p->printed = p->precision + len + ((n < 0) ? 1 : 0);
	decimal = ((n < 0.0f) ? -n : n);
	decimal = (decimal - (long)(((n < 0.0f) ? -n : n))) *
	ft_pow(10, p->precision + 1);
	decimal = ((long)decimal % 10 > 4) ? (decimal) / 10 + 1 : decimal / 10;
	value = (int)decimal;
	ldtoa_fill(n, p, value);
}
*/




























int	str_rounder(char *str, int i)
{
	while (i >= 0 && (str[i] == '9' || str[i] == '.'))
		if (str[i] == '9')
			str[i--] = '0';
	if (i < 0)
		return (1);
	str[i]++;
	return (0);
}

void write_str(long long int intpart, char *pt, int i)
{
	if (intpart / 10)
		write_str(intpart / 10, pt, i - 1);
	pt[i] = intpart % 10 + '0';
}

void	write_lobby_double(double doub, t_flags *flags, int size)
{
	long long int	intpart;
	int		limit;
	int		i;
	char		temp[100];

	limit = 6;
	if (flags->bw_flags & PRECIS)
		limit = flags->precision_val;
	if (!limit)
		doub += 0.5;
	intpart = doub < 0.0 ? -doub : doub;
	write_str(intpart, temp, size - 1);
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
	if (doub > 0.5)
	{
		if (str_rounder(temp, i + size - 1))
			write_char_buffer('1', 1);
	}
	write_str_buffer(temp, size + i);
}







void	write_double_pos(double doub, t_flags *flags, int sizetoprint)
{
	if (flags->bw_flags & MINUS)
	{
		write_lobby_double(doub, flags, sizetoprint);
		write_char_buffer(' ', flags->field_width_val - sizetoprint);
	}
	else
	{
		if (flags->bw_flags & ZERO)
			write_char_buffer('0', flags->field_width_val - sizetoprint);
		else
			write_char_buffer(' ', flags->field_width_val - sizetoprint);
		write_lobby_double(doub, flags, sizetoprint);
	}
}

void	write_double_neg_nobound(double doub, t_flags *flags, int sizetoprint)
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
	write_lobby_double(doub, flags, sizetoprint);
}

void	write_double_neg(double doub, t_flags *flags, int sizetoprint)
{
	int	space_toprint;
	
	if (!(flags->bw_flags & MINUS))
		write_double_neg_nobound(doub, flags, sizetoprint);
	else
	{
		space_toprint = flags->field_width_val - sizetoprint;
		write_char_buffer('-', 1);
		write_lobby_double(doub, flags, sizetoprint);
		write_char_buffer(' ', space_toprint);
	}
}

void	write_f(va_list *param, t_flags *flags)
{
	double	doub;
	int	sizetoprint;

	doub = va_arg(*param, double);
	//neg = doub < 0 ? 1 : 0;
	//doub = doub < 0 ? -doub : doub;
	sizetoprint = my_utoa_len(doub < 0.0 ? -doub : doub, 10, NULL);
	if (flags->bw_flags & PRECIS)
	       	sizetoprint += flags->precision_val == 0 ? 0 : 1 + flags->precision_val;
	else
		sizetoprint += 7;
	if (doub < 0.0f || doub == -0.0)
		write_double_neg(-doub, flags, sizetoprint + 1);
	else
		write_double_pos(doub, flags, sizetoprint);
}
