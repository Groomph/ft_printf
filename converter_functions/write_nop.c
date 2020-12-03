/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_nop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:03:15 by romain            #+#    #+#             */
/*   Updated: 2020/12/03 12:41:03 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void		write_n(va_list *param, t_pars *pars)
{
	int	*pt;

	if (pars)
	{
		pt = va_arg(*param, int*);
		*pt = send_totalsize();
	}
}

void			write_p(va_list *param, t_pars *pars)
{
	unsigned long	pt;
	char		tab[3];
	int		i;

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

void    write_o(va_list *param, t_pars *pars)
{
        unsigned int    nb;
        char            zero;

        nb = va_arg(*param, unsigned int);
        if (pars->bw_flags & CROISI &&
                        my_utoa_len(nb, 8) > pars->precision_val)
        {
                zero = '0';
                pars->extra_before = &zero;
                pars->size_extra = 1;
        }
	lobby_numeric_converter(nb, "01234567", pars, 8);
}
