/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_diuxx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez </var/mail/rsanchez>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:37:58 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/03 13:44:15 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	set_comp_num(t_pars *pars)
{
	if (pars->precision_val > pars->size_str)
	{
		pars->zero_before += (pars->precision_val - pars->size_str);
		pars->field_width_val -= pars->precision_val + pars->size_extra;
	}
	else
		pars->field_width_val -= (pars->size_str + pars->size_extra);
	add_sign_numeric(pars, pars->sign);
	if (pars->field_width_val > 0)
		fill_width(pars, pars->field_width_val);
	write_into_buffer(pars);
}

void	lobby_numeric_converter(unsigned long long int nb, char *base,
							t_pars *pars, int sizeb)
{
	char	tab[50];
	int	i;

	if (pars->bw_flags & ZERO && pars->bw_flags & PRECIS)
		pars->bw_flags &= ~(ZERO);
	else if (!(pars->bw_flags & PRECIS))
	{
		pars->bw_flags |= PRECIS;
		pars->precision_val = 1;
	}		
	pars->str = tab;
	pars->size_str = 0;
	if (!((pars->bw_flags & PRECIS) && pars->precision_val == 0 && nb == 0))
		pars->size_str = my_utoa_len(nb, sizeb);
	i = pars->size_str;
	while (--i >= 0)
	{
		tab[i] = base[nb % sizeb];
		nb /= sizeb;
	}
	set_comp_num(pars);
}

void	write_di(va_list *param, t_pars *pars)
{
	int	nb;

	nb = va_arg(*param, int);
	if (nb < 0)
	{
		pars->sign = '-';
		lobby_numeric_converter((unsigned int)-nb,
						"0123456789", pars, 10);
	}
	else
	{
		if (pars->bw_flags & SPACE || pars->bw_flags & PLUS)
			pars->sign = '+';
		lobby_numeric_converter((unsigned int)nb,
						"0123456789", pars, 10);
	}
}

void	write_u(va_list *param, t_pars *pars)
{
	unsigned int	nb;
	
	nb = va_arg(*param, unsigned int);
/*	if (nb && pars->bw_flags & PLUS)
		pars->space_before++;
*/	lobby_numeric_converter(nb, "0123456789", pars, 10);
}

void	write_x(va_list *param, t_pars *pars)
{
	unsigned int	nb;
	char		tab[2];
	
	nb = va_arg(*param, unsigned int);
	if (nb && pars->bw_flags & CROISI)	
	{
		tab[0] = '0';
		tab[1] = 'x';
		pars->extra_before = tab;
		pars->size_extra = 2;
	}
/*	else if (nb && ((pars->bw_flags & SPACE) || (pars->bw_flags & PLUS)))
	{
		pars->space_before++;
		if (pars->bw_flags & SPACE)
			pars->field_width_val--;
	}
*/	lobby_numeric_converter(nb, "0123456789abcdef", pars, 16);
}

void	write_xx(va_list *param, t_pars *pars)
{
	unsigned int	nb;
	char		tab[2];

	nb = va_arg(*param, unsigned int);
	if (nb && pars->bw_flags & CROISI)	
	{
		tab[0] = '0';
		tab[1] = 'X';
		pars->extra_before = tab;
		pars->size_extra = 2;
	}
/*	else if (nb && ((pars->bw_flags & SPACE) || (pars->bw_flags & PLUS)))
	{
		pars->space_before++;
		if (pars->bw_flags & SPACE)
			pars->field_width_val--;
	}	
*/	lobby_numeric_converter(nb, "0123456789ABCDEF", pars, 16);
}
