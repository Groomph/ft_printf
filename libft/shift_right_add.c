/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_right_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 07:52:08 by romain            #+#    #+#             */
/*   Updated: 2020/12/04 08:40:59 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	shift_right_add(char *str, char c, int i)
{
	char	tmp;

	if (!str || !str[i])
	{
		if (!str)
			return (-1);
		str[i] = c;
		str[i + 1] = '\0';
		return (i + 1);
	}
	tmp = str[i];
	str[i] = c;
	return (shift_right_add(str, tmp, i + 1));
}
