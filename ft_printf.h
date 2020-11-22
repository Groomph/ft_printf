/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/22 22:17:01 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <unistd.h>

# define BUFFER_SIZE 100

typedef	struct	s_buffer
{
	int			i;
	int			totalsize;
	char		bufstr[BUFFER_SIZE];
}				t_buffer;

typedef struct	s_flags
{
	int			boundary_left;
	int			zero_padded;
	int			precision_bool;
	int			precision_val;
	int			field_width_val;
	char		convert_char;
}				t_flags;

typedef struct	s_converter
{
	void			(*pt_function)(va_list *param, t_flags *flags);
	char			c;
}				t_converter;

int				ft_printf(const char *str, ...);
int				ft_printf_parsing(char *str, va_list *param);
void				lobby_write_buffer(va_list *param, t_flags *flags);

/*
****************   buffer   ****************
*/

void				print_buffer(int fd);
void				write_str_buffer(char *str, int size);
void				write_char_buffer(char c, int nb);
int				send_totalsize(void);
void				init_buffer(void);

/*
****************   print_iduxXcs%p.c   ****************
*/

void				write_di(va_list *param, t_flags *flags);
void				write_u(va_list *param, t_flags *flags);
void				write_x(va_list *param, t_flags *flags);
void				write_X(va_list *param, t_flags *flags);
void				write_c(va_list *param, t_flags *flags);
void				write_s(va_list *param, t_flags *flags);
void				write_PCT(t_flags *flags);
void				write_p(va_list *param, t_flags *flags);

/*
****************   buffer_utils.c   ****************
*/

void				write_base_recurs(unsigned long pt, char *base, int sizeb, int sizetopr);
int				my_my_strlen(char *str);
int				my_utoa_len(unsigned long nb, int sizebase, t_flags *flags);

#endif
