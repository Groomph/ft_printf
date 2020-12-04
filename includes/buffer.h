/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 05:19:35 by romain            #+#    #+#             */
/*   Updated: 2020/12/04 05:21:24 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <unistd.h>

# define BUFFER_SIZE 100

typedef	struct	s_buffer
{
	int			i;
	int			totalsize;
	char		bufstr[BUFFER_SIZE];
}				t_buffer;

void				print_buffer(int fd);
void				write_str_buffer(const char *str, int size);
void				write_char_buffer(char c, int nb);
int				send_totalsize(void);
void				init_buffer(void);

#endif
