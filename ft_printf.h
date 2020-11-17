/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/17 18:29:06 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_pars
{
	int boundary_left;
	int zero_padded;
	int precision_bool;
	int precision_val;
	int field_width_val;
	char convert_char;
	char *todisplay;
}		t_pars;

int	ft_printf_parsing(char *str, va_list *param, int *count);
int	ft_printf_print(t_pars *pars, va_list *param);
int	print_signed_digit(char tab[], int size, t_pars *pars);
int	print_unsigned_digit(char *str, int size, t_pars *pars);
int	print_string(char *str, t_pars *pars, char *strnull, char *strvide);
int	print_addr_hexa(unsigned long pt, int base, int i, t_pars *pars);

#endif
