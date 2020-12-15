/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 22:51:17 by romain            #+#    #+#             */
/*   Updated: 2020/12/15 13:31:32 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_H
# define FLOAT_H

# include "ft_printf.h"

typedef struct	s_double
{
	long double	doub;
	char		strdoub[150];
	short		point;
	short		size;
	short		exponent;
	char		sign;
	short		isnull;
}				t_doub;

int				digit_str_rounder(t_doub *doub, int i);
void			divide_str_double(t_doub *doub);
void			multiply_str_double(t_doub *doub);
t_doub			find_exponent(t_doub doub, int index);
void			init_struct_double(t_doub *doub);
int				is_roundable_bynb(t_doub doub, int index);
void			round_float(t_doub *doub, int index);
void			write_exponent(int exponent, char *tab);
int				count_trailing_zero(t_doub *doub, int index);
int				check_float_coherence(t_pars *pars,
							long double doub);

#endif
