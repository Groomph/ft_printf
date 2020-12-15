/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_infinite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:46:21 by romain            #+#    #+#             */
/*   Updated: 2020/12/15 12:16:20 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_infinite(long double doub)
{
	unsigned int	up;
	float			inf;

	up = 0xFF800000;
	inf = *(float *)&up;
	if (doub == inf)
		return (-1);
	up = 0x7F800000;
	inf = *(float *)&up;
	if (doub == inf)
		return (1);
	return (0);
}
