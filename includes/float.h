/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 22:51:17 by romain            #+#    #+#             */
/*   Updated: 2020/12/05 11:16:54 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_H
# define FLOAT_H

typedef struct  s_double
{
	long double doub;
        char    strdoub[150];
        short     point;
	short	size;
        short     exponent;
        char     sign;
        short     isnull;
}       	t_doub;

int     digit_str_rounder(t_doub *doub, int i);
void    divide_str_double(t_doub *doub);
void    multiply_str_double(t_doub *doub);
t_doub     find_exponent(t_doub doub, int index);
void    init_struct_double(t_doub *doub);
int	is_roundable_bynb(t_doub doub, int index);
void    round_float(t_doub *doub, int index);
int     count_trailing_zero(t_doub *doub, int index);
void	write_exponent(int exponent, char *tab);

#endif
