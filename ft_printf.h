/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/20 17:05:31 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <unistd.h>

# define BUFFER_SIZE 100

typedef struct	s_pars
{
	int			boundary_left;
	int			zero_padded;
	int			precision_bool;
	int			precision_val;
	int			field_width_val;
	char		convert_char;
}				t_pars;

typedef struct	s_buffer
{
	int			i;
	int			totalsize;
	char		buf[BUFFER_SIZE];
	t_pars			pars;
}				t_buffer;

int				ft_printf(const char *str, ...);

int				ft_printf_parsing(char *str,
							t_buffer *buf, va_list *param);
void				ft_printf_print(t_buffer *buf, va_list *param);
/*
****************   buffer   ****************
*/

void				write_str_buffer(t_buffer *buf,
							char *str, int size);
void				write_char_buffer(t_buffer *buf,
							char c, int nb);

/*
****************   print_iduxX.c   ****************
*/
void				write_signed_boundary(t_buffer *buf, char tab[],
							int size);
void				write_unsigned_digit(t_buffer *buf, char *str,
							int size);
/*
****************   print_cs.c   ****************
*/

void				write_char_null(t_buffer *buf);
void				write_string(t_buffer *buf, char *str, char *strnull);

/*
****************   print_p.c   ****************
*/

void				write_addr_hexa(t_buffer *buf, unsigned long pt);

/*
****************   buffer_utils.c   ****************
*/

int				my_strlen(char *str);
int				my_utoa_len(unsigned long nb, int sizebase);

#endif
