/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 05:19:35 by romain            #+#    #+#             */
/*   Updated: 2020/12/15 13:25:54 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <unistd.h>
# include <wchar.h>

# define BUFFER_SIZE 100

typedef	struct	s_buffer
{
	int			i;
	int			totalsize;
	char		bufstr[BUFFER_SIZE];
}				t_buffer;

int				print_buffer(int fd);
void			write_str_buffer(const char *str, int size);
void			write_char_buffer(char c, int nb);
int				write_widechar_buffer(wchar_t c, int size);
void			init_buffer(void);

#endif
