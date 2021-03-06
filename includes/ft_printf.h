/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:31:05 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:31:57 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "buffer.h"
# include "../libft/libft.h"

enum	e_bitwize
{
	MINUS = (1U << 1),
	ZERO = (1U << 2),
	PRECIS = (1U << 3),
	SPACE = (1U << 4),
	CROISI = (1U << 5),
	PLUS = (1U << 6),
	LL = (1U << 10),
	LLLL = (1U << 11),
	HH = (1U << 12),
	HHHH = (1U << 13)
};

typedef struct			s_pars
{
	short				bw_flags;
	int					precision_val;
	int					field_width_val;
	char				convert_char;
	short				space_before;
	char				*extra_before;
	short				zero_before;
	char				sign;
	char				*str;
	short				zero_after;
	char				*extra_after;
	short				space_after;
	short				print_sign;
	short				size_str;
	short				size_extra;
}						t_pars;

typedef struct			s_converter
{
	void				(*pt_function)(va_list *param, t_pars *pars);
	char				c;
}						t_converter;

int						ft_printf(const char *str, ...);
int						ft_printf_parsing(const char *str, va_list *param);
int						lobby_write_buffer(va_list *param, t_pars *pars);

/*
****************   parsing & composition   ****************
*/

int						field_width(t_pars *pars, va_list *param,
														const char *str);
int						precision(t_pars *pars, va_list *param,
														const char *str);
void					fill_width(t_pars *pars, int remains);
void					add_sign_numeric(t_pars *pars, char sign);

/*
****************   print_efgidouxXpcs%.c   ****************
*/

void					write_di(va_list *param, t_pars *pars);
void					write_u(va_list *param, t_pars *pars);
void					write_xx(va_list *param, t_pars *pars);
void					write_c(va_list *param, t_pars *pars);
void					write_s(va_list *param, t_pars *pars);
void					write_pct(va_list *param, t_pars *pars);
void					write_p(va_list *param, t_pars *pars);
void					write_o(va_list *param, t_pars *pars);
void					write_n(va_list *param, t_pars *pars);
void					write_ef(va_list *param, t_pars *pars);
void					write_g(va_list *param, t_pars *pars);
void					write_b(va_list *param, t_pars *pars);
int						coloring_bonus(char *str);
void					set_comp_num(t_pars *pars);
void					write_into_buffer(t_pars *pars, wchar_t *wstr);
unsigned long long int	get_unsigned_param(va_list *param, t_pars *pars);
void					lobby_numeric_converter(unsigned long long int nb,
						char *base, t_pars *pars, int sizeb);
int						widestring_len(wchar_t *str, t_pars *pars);
#endif
