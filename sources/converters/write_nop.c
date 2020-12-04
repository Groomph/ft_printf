/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_nop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:03:15 by romain            #+#    #+#             */
/*   Updated: 2020/12/04 14:16:58 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "buffer.h"

void		write_n(va_list *param, t_pars *pars)
{
	void	*pt;
	int	tmp;

	pt = va_arg(*param, void*);
	tmp = send_totalsize();
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
        unsigned long long int    nb;
        char            zero;
	
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
