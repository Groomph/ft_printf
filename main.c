/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:09:13 by romain            #+#    #+#             */
/*   Updated: 2020/11/16 17:49:58 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int ft_printf(const char *str, ...);

int main(void)
{
	char *str = "Classique///Coucou bande de nouille\n";
	char *str2 = "INT///Coucou bande %-10.6d nouille %i\n";
	char *str3 = "HEXA///Coucou bande %x nouille %x\n";
	char *str4 = "STRING///Coucou bande %s %s\n";
	char *str5 = "ADDRESS///Coucou bande %-p\n";
	char *str7 = "ADDRESS///Coucou bande %20p\n";
	char *str8 = "ADDRESS///Coucou bande %.20p\n";
	char *str9 = "ADDRESS///Coucou bande %20.20p\n";
	char *str6 = "UNSIGNEDINT///Coucou bande %u\n";
	int	i = 0;
	int	i2 = 0;
	
	i = printf(str);
	i2 = ft_printf(str);
	printf("printf: %d    ft_printf: %d\n", i, i2);

	i = printf(str2, 222, 23);
	i2 = ft_printf(str2, 222, 23);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf(str3, 10, 10, -2222, -233);
	i2 = ft_printf(str3, 10, 10, -2222, -233);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf(str4, NULL, "aled", "dur");
	i2 = ft_printf(str4, NULL, "aled", "dur");
	printf("printf: %d    ft_printf: %d\n", i, i2);

	char *p = NULL;
	p = &i;

	i = printf(str6, -999);
	i2 = ft_printf(str6, -999);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf(str5, p);
	i2 = ft_printf(str5, p);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf(str7, p);
	i2 = ft_printf(str7, p);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf(str8, p);
	i2 = ft_printf(str8, p);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf(str9, p);
	i2 = ft_printf(str9, p);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	return (0);
}
