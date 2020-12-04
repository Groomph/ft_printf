/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:58:50 by romain            #+#    #+#             */
/*   Updated: 2020/12/04 09:27:10 by romain           ###   ########.fr       */
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

static int	second_pars(const char *str, int i, t_pars *pars, va_list *param)
{
	if (str[i] == '*' || (str[i] <= '9' && str[i] >= '1'))
		i += field_width(pars, param, &str[i]);
	else if (str[i] == '.')
		i += precision(pars, param, &str[i]);
	else
		return (i);
	return (second_pars(str, i, pars, param));
}

static int	first_pars(const char *str, int i, t_pars *pars)
{
	if (str[i] == '-')
		pars->bw_flags |= MINUS;
	else if (str[i] == '0')
		pars->bw_flags |= ZERO;
	else if (str[i] == ' ')
		pars->bw_flags |= SPACE;
	else if (str[i] == '#')
		pars->bw_flags |= CROISI;
	else if (str[i] == '+')
		pars->bw_flags |= PLUS;
	else
		return (i);
	return (first_pars(str, i + 1, pars));
}

int			ft_printf_parsing(const char *str, va_list *param)
{
	int		i;
	va_list		param2;
	t_pars		pars;
	
	init_zero(&pars, sizeof(pars));
	va_copy(param2, *param);
	i = first_pars(str, 1, &pars);
	i += second_pars(&str[i], 0, &pars, &param2);
	i += third_pars(&str[i], 0, &pars);
	erase_conflicting_flags(&pars);	
	if (str[i])
			pars.convert_char = str[i++];
	if (!lobby_write_buffer(&param2, &pars))
		write_str_buffer(str, i);
	else
		va_copy(*param, param2);
	return (i);
}
