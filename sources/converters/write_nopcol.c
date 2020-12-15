/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_nopcol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:37:44 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:37:46 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "buffer.h"

static int	coloring_next(char *str)
{
	if (!str_comp("{Fblack}", str, 8))
		write_str_buffer("\033[40m", 5);
	else if (!str_comp("{Fred}", str, 6))
		write_str_buffer("\033[41m", 5);
	else if (!str_comp("{Fgreen}", str, 8))
		write_str_buffer("\033[42m", 5);
	else if (!str_comp("{Fyellow}", str, 9))
		write_str_buffer("\033[43m", 5);
	else if (!str_comp("{Fblue}", str, 7))
		write_str_buffer("\033[44m", 5);
	else if (!str_comp("{Fmagenta}", str, 10))
		write_str_buffer("\033[45m", 5);
	else if (!str_comp("{Fcyan}", str, 7))
		write_str_buffer("\033[46m", 5);
	else if (!str_comp("{Fwhite}", str, 8))
		write_str_buffer("\033[47m", 5);
	else if (!str_comp("{Fblack2}", str, 9))
		write_str_buffer("\033[48m", 5);
	else if (!str_comp("{Fdefault}", str, 10))
		write_str_buffer("\033[49m", 5);
	else
		return (0);
	return (1);
}

int			coloring_bonus(char *str)
{
	print_buffer(1);
	if (!str_comp("{black}", str, 7))
		write_str_buffer("\033[30m", 5);
	else if (!str_comp("{red}", str, 5))
		write_str_buffer("\033[31m", 5);
	else if (!str_comp("{green}", str, 7))
		write_str_buffer("\033[32m", 5);
	else if (!str_comp("{yellow}", str, 8))
		write_str_buffer("\033[33m", 5);
	else if (!str_comp("{blue}", str, 6))
		write_str_buffer("\033[34m", 5);
	else if (!str_comp("{magenta}", str, 9))
		write_str_buffer("\033[35m", 5);
	else if (!str_comp("{cyan}", str, 6))
		write_str_buffer("\033[36m", 5);
	else if (!str_comp("{white}", str, 7))
		write_str_buffer("\033[37m", 5);
	else if (!str_comp("{black2}", str, 8))
		write_str_buffer("\033[38m", 5);
	else if (!str_comp("{default}", str, 9))
		write_str_buffer("\033[39m", 5);
	else
		return (coloring_next(str));
	return (1);
}

void		write_n(va_list *param, t_pars *pars)
{
	void	*pt;
	int		tmp;

	pt = va_arg(*param, void*);
	tmp = print_buffer(1);
	if (pars->bw_flags & HHHH)
		*(char*)pt = (char)tmp;
	else if (pars->bw_flags & HH)
		*(short*)pt = (short)tmp;
	else if (pars->bw_flags & LLLL)
		*(long long int*)pt = tmp;
	else if (pars->bw_flags & LL)
		*(long int*)pt = tmp;
	else
		*(int*)pt = tmp;
}

void		write_p(va_list *param, t_pars *pars)
{
	unsigned long	pt;
	char			tab[3];
	int				i;

	i = 0;
	pt = va_arg(*param, unsigned long);
	pars->extra_before = tab;
	if (pars->bw_flags & PLUS)
		tab[i++] = '+';
	else if (pars->bw_flags & SPACE)
		pars->sign = '+';
	tab[i++] = '0';
	tab[i++] = 'x';
	pars->size_extra = i;
	lobby_numeric_converter(pt, "0123456789abcdef", pars, 16);
}

void		write_o(va_list *param, t_pars *pars)
{
	unsigned long long int	nb;
	char					zero;

	nb = get_unsigned_param(param, pars);
	if (pars->bw_flags & CROISI &&
			utoa_len(nb, 8) > pars->precision_val)
	{
		zero = '0';
		pars->extra_before = &zero;
		pars->size_extra = 1;
	}
	lobby_numeric_converter(nb, "01234567", pars, 8);
}
