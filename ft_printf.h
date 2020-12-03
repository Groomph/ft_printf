/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/12/03 14:57:48 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <unistd.h>

# define BUFFER_SIZE 100

# define MINUS (1U << 1)
# define ZERO (1U << 2)
# define PRECIS (1U << 3) 
# define SPACE (1U << 4)
# define CROISI (1U << 5)
# define PLUS (1U << 6)

# define LL (1U << 10)
# define LLLL (1U << 11)
# define HH (1U << 12)
# define HHHH (1U << 13)

typedef	struct	s_buffer
{
	int			i;
	int			totalsize;
	char		bufstr[BUFFER_SIZE];
}				t_buffer;

typedef struct	s_pars
{
	unsigned int		bw_flags;
	int			precision_val;
	int			field_width_val;
	char			convert_char;
/**/
	short			space_before;
	char			*extra_before;
	short			zero_before;
	char			sign;
	char			*str;
	short			zero_after;
	char			*extra_after;
	short			space_after;
	short			print_sign;
	short			size_str;
	short			size_extra;
}				t_pars;

typedef struct	s_converter
{
	void			(*pt_function)(va_list *param, t_pars *pars);
	char			c;
}				t_converter;

int				ft_printf(const char *str, ...);
int				ft_printf_parsing(const char *str, va_list *param);
int				lobby_write_buffer(va_list *param,
								t_pars *pars);
/*
****************   buffer   ****************
*/

void				print_buffer(int fd);
void				write_str_buffer(const char *str, int size);
void				write_char_buffer(char c, int nb);
int				send_totalsize(void);
void				init_buffer(void);

/*
****************   parsing & composition   ****************
*/

int				field_width(t_pars *pars, va_list *param, const char *str);
int				precision(t_pars *pars, va_list *param, const char *str);
void            		fill_width(t_pars *pars, int remains);
void            		add_sign_numeric(t_pars *pars, char sign);


/*
****************   print_efgidouxXpcs%.c   ****************
*/

void    lobby_numeric_converter(unsigned long long int nb, char *base,
                                                 t_pars *pars, int sizeb);
void				set_comp_num(t_pars *pars);
void				write_into_buffer(t_pars *pars);
void				write_di(va_list *param, t_pars *pars);
void				write_u(va_list *param, t_pars *pars);
void				write_x(va_list *param, t_pars *pars);
void				write_xx(va_list *param, t_pars *pars);
void				write_c(va_list *param, t_pars *pars);
void				write_s(va_list *param, t_pars *pars);
void				write_pct(va_list *param, t_pars *pars);
void				write_p(va_list *param, t_pars *pars);
void				write_o(va_list *param, t_pars *pars);
void				write_n(va_list *param, t_pars *pars);
void				write_e(va_list *param, t_pars *pars);
void				write_f(va_list *param, t_pars *pars);
void				write_g(va_list *param, t_pars *pars);
/*
****************   write_utils.c   ****************
*/

void				write_base_recurs(unsigned long long pt, char *base,
						int sizeb, int sizetopr);
void    			write_digit_str(unsigned long long int intpart,
								char *pt, int i);

int				my_my_strlen(char *str);
int				my_utoa_len(unsigned long long nb, int sizebase);
int				ft_is_signed(long double lf);

#endif
