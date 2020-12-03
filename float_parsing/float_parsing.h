/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 22:51:17 by romain            #+#    #+#             */
/*   Updated: 2020/12/03 14:48:49 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_PARSING_H
# define FLOAT_PARSING_H

# include "../ft_printf.h"

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

int     shift_left_erase(char *str, int i);
int     shift_right_add(char *str, char c, int i);
int     digit_str_rounder(t_doub *doub, int i);
void    divide_str_double(t_doub *doub);
void    multiply_str_double(t_doub *doub);
t_doub     find_exponent(t_doub doub, int index);
void    init_struct_double(t_doub *doub);
int	is_roundable_bynb(t_doub doub, int index);
void    round_float(t_doub *doub, int index);
int     count_clean_zero(t_doub *doub, int index, int count_clean);
void	write_exponent(int exponent, char *tab);

#endif
