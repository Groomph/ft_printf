/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_left_erase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 07:55:08 by romain            #+#    #+#             */
/*   Updated: 2020/12/04 08:41:47 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	shift_left_erase(char *str, int i)
{
	if (!str)
		return (-1);
	str[i] = str[i + 1];
	if (str[i])
		return (shift_left_erase(str, i + 1));
	else
		return (i);
}
