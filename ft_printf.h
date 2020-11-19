/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/19 23:58:19 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_pars
{
	int			boundary_left;
	int			zero_padded;
	int			precision_bool;
	int			precision_val;
	int			field_width_val;
	char		convert_char;
	char		*todisplay;
}				t_pars;

int				ft_printf(const char *str, ...);

int				ft_printf_parsing(char *str,
									va_list *param, int *count);
int				ft_printf_print(t_pars *pars,
									va_list *param);
/*
****************   ft_printf_print_int.c   ****************
*/
int				print_signed_boundary(char tab[],
									int size, t_pars *pars);
int				print_unsigned_digit(char *str,
									int size, t_pars *pars);
/*
****************   ft_printf_print2.c   ****************
*/

int				print_char_null(t_pars *pars);
int				print_string(char *str, t_pars *pars, char *strnull);
int				print_addr_hexa(unsigned long pt, t_pars *pars);
#endif
