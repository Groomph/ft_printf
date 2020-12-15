/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 04:13:52 by romain            #+#    #+#             */
/*   Updated: 2020/12/15 12:28:40 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

/*
******************   BYTEWISE & MEMORY  ******************
*/

void	init_zero(void *pt, size_t i);

/*
*******************  IS? FONCTIONS  *******************
*/

int		is_double_signed(long double doub);
int		is_not_number(long double doub);
int		is_infinite(long double doub);

/*
*******************  CHAR & STRING  *******************
*/

char	*substr_free(char *s, size_t start, size_t len, int freestr);
char	*strjoin_free(char *s1, char *s2, int freestr1, int freestr2);
size_t	string_len(const char *s);
int		shift_right_add(char *str, char c, int i);
int		shift_left_erase(char *str, int i);
int		str_comp(char *str, char *str2, int stop);

int		utoa_len(unsigned long long nb, int sizebase);
int		utoa_base(unsigned long long nb, char *dest, char *base, int sizebase);

#endif
