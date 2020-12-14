/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:58:50 by romain            #+#    #+#             */
/*   Updated: 2020/12/14 22:39:23 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	erase_conflicting_flags(t_pars *pars)
{
	if (pars->bw_flags & PLUS && pars->bw_flags & SPACE)
		pars->bw_flags &= ~(SPACE);
	if (pars->bw_flags & MINUS && pars->bw_flags & ZERO)
		pars->bw_flags &= ~(ZERO);
}

static int	third_pars(const char *str, int i, t_pars *pars)
{
	if (str[i] == 'l' && str[i + 1] == 'l')
	{
		i++;
		pars->bw_flags |= LLLL;
	}
	else if (str[i] == 'h' && str[i + 1] == 'h')
	{
		i++;
		pars->bw_flags |= HHHH;
	}
	else if (str[i] == 'l')
		pars->bw_flags |= LL;
	else if (str[i] == 'h')
		pars->bw_flags |= HH;
	else
		return (i);
	return (third_pars(str, i + 1, pars));
}

static int	second_pars(const char *s, int i, t_pars *pars, va_list *param)
{
	if (s[i] == '*' || (s[i] <= '9' && s[i] >= '1'))
		i += field_width(pars, param, &s[i]);
	else if (s[i] == '.')
		i += precision(pars, param, &s[i]);
	else
		return (third_pars(s, i, pars));
	return (second_pars(s, i, pars, param));
}

static int	first_pars(const char *s, int i, t_pars *pars, va_list *param)
{
	if (s[i] == '-')
		pars->bw_flags |= MINUS;
	else if (s[i] == '0')
		pars->bw_flags |= ZERO;
	else if (s[i] == ' ')
		pars->bw_flags |= SPACE;
	else if (s[i] == '#')
		pars->bw_flags |= CROISI;
	else if (s[i] == '+')
		pars->bw_flags |= PLUS;
	else
		return (second_pars(s, i, pars, param));
	return (first_pars(s, i + 1, pars, param));
}

int			ft_printf_parsing(const char *str, va_list *param)
{
	int			i;
	va_list		param2;
	t_pars		pars;
	char		tab[12];

	init_zero(&pars, sizeof(pars));
	va_copy(param2, *param);
	i = first_pars(str, 1, &pars, &param2);
	erase_conflicting_flags(&pars);
	if (str[i] && str[i] != '{')
		pars.convert_char = str[i++];
	else if (i == 1 && str[i] == '{')
	{
		i = 0;
		while (++i < 11 && str[i] && str[i] != '}')
			tab[i - 1] = str[i];
		tab[i - 1] = str[i];
		tab[i++] = '\0';
		pars.str = tab;
	}
	if (!lobby_write_buffer(&param2, &pars))
		write_str_buffer(str, i);
	else
		va_copy(*param, param2);
	return (i);
}
