/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:09:13 by romain            #+#    #+#             */
/*   Updated: 2020/12/01 11:07:09 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"


int ft_printf(const char *str, ...);

int main(void)
{
	char *str = "Classique///Coucou bande de nouille\n";
//	char *str2 = "INT///Coucou bande %0-10.6i nouille %010.6i\n";
//	char *str20 = "hi low";
//	char *str21 = "INT///Coucou bande %0-10.6i nouille %010.6i\n";
/*	char *str22 = "INT///Coucou bande %0-10.6i nouille %010.6i\n";
	char *str3 = "HEXA///Coucou bande %-20.0x nouille %-10x\n";
	char *str4 = "STRING///Coucou bande %s %s\n";
	char *str11 = "%s";
	char *str5 = "ADDRESS///Coucou bande %-p\n";
	char *str7 = "ADDRESS///Coucou bande %-2p\n";
	char *str8 = "ADDRESS///Coucou bande %-1p\n";
	char *str9 = "ADDRESS///Coucou bande %-20.20p\n";
	char *str10 = "char///Couco%-2c ban%%de de %3c\n";
	char *str6 = "UNSIGNEDINT///Coucou %-.0ubande %-10u\n";

	i = printf("%*i, %*d, %*d, %*d, %*d, %*d, %*u, %*x, %*X\n", a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0);
	i2 = ft_printf("%*i, %*d, %*d, %*d, %*d, %*d, %*u, %*x, %*X\n", a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0);
		
	printf("printf: %d    ft_printf: %d\n", i, i2);
*/
	int	i = -2.9999999;
	int	i2 = -2.40;
	double test = -129083211111.12366666;
	    i = printf("printf:    %.15g\n", test);
	i2 = ft_printf("ft_printf: %.15g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 3.001;
	    i = printf("printf:    %-4.3g\n", test);
	i2 = ft_printf("ft_printf: %-4.3g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 3.601;
	    i = printf("printf:    %-4.4g\n", test);
	i2 = ft_printf("ft_printf: %-4.4g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 3.601;
	    i = printf("printf:    %-4.*g\n", 8, test);
	i2 = ft_printf("ft_printf: %-4.*g\n", 8, test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 1.20026416000;
	    i = printf("printf:    %-4.*g\n", 8, test);
	i2 = ft_printf("ft_printf: %-4.*g\n", 8, test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 0.600013;
	    i = printf("printf:    %-4.4g\n", test);
	i2 = ft_printf("ft_printf: %-4.4g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 0.6000001367;
	    i = printf("printf:    %-4g\n", test);
	i2 = ft_printf("ft_printf: %-4g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 3.0;
	    i = printf("printf:    %-4.2g\n", test);
	i2 = ft_printf("ft_printf: %-4.2g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 3.00030003000300025;
	    i = printf("printf:    %-4.16e\n", test);
	i2 = ft_printf("ft_printf: %-4.16e\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 1000000000000000000000.2;
	    i = printf("printf:    %.1g\n", test);
	i2 = ft_printf("ft_printf: %.1g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 9999999999999999.2;
	    i = printf("printf:    %.1g\n", test);
	i2 = ft_printf("ft_printf: %.1g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

test = -1797693134862315708145418276846754670.88889;
//	test = 555555555555222222222222222222222222222222222222222299999999999999999999999999999999999999999999999999999999999999.2;
	    i = printf("printf:    %g\n", test);
	i2 = ft_printf("ft_printf: %g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = -3.6004;
	    i = printf("printf:    %4.3g\n", test);
	i2 = ft_printf("ft_printf: %4.3g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = -5.7848744;
	    i = printf("printf:    %11.*g\n", -1, test);
	i2 = ft_printf("ft_printf: %11.*g\n", -1, test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 222.50000;
	    i = printf("printf:    %20.10g\n", test);
	i2 = ft_printf("ft_printf: %20.10g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 223.50000;
	    i = printf("printf:    %-15.8g\n", test);
	i2 = ft_printf("ft_printf: %-15.8g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 0.000000;
	    i = printf("printf:    %.g\n", test);
	i2 = ft_printf("ft_printf: %.g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = -0.500000;
	    i = printf("printf:    %.g\n", test);
	i2 = ft_printf("ft_printf: %.g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 303.37647788;
	    i = printf("printf:    %-4.3g\n", test);
	i2 = ft_printf("ft_printf: %-4.3g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 3444444444444403.37647788;
	    i = printf("printf:    %-4.4g\n", test);
	i2 = ft_printf("ft_printf: %-4.4g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 303.376477444488;
	    i = printf("printf:    %-4.5g\n", test);
	i2 = ft_printf("ft_printf: %-4.5g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 123.1234550000000000000000000000000000000000000000000000000000000000000000000;
	    i = printf("printf:    %-4.5f\n", test);
	i2 = ft_printf("ft_printf: %-4.5f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 5.55555;
	double test3 = 4.55555;
	double test2 = test - 0.10000;
	double test4 = (test * 10 - 1) / 10;
	    i = printf("printf:    %#-4.20g\n", test);
	    i = printf("printf:    %#-4.20g\n", test3);
	    i = printf("printf:    %#-4.20g\n", test2);
	    i = printf("printf:    %020.10e\n", test4);
	i2 = ft_printf("ft_printf: %020.10e\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
/*	
	
	

	test = -2.8137310073157007;
	i = printf("printf:    %-4.*f\n", 16, test);
	i2 = ft_printf("ft_printf: %-4.*f\n", 16, test);
	printf("printf: %d    ft_printf: %d\n", i, i2);

	test = -2.8137310073157007000;
	i = printf("printf:    %-4.*f\n", 17, test);
	i2 = ft_printf("ft_printf: %-4.*f\n", 17, test);
	printf("printf: %d    ft_printf: %d\n", i, i2);

	test = -2.813731007310567899999999999;
	i = printf("printf:    %-4.*f\n", 20, test);
	i2 = ft_printf("ft_printf: %-4.*f\n", 20, test);
	printf("printf: %d    ft_printf: %d\n", i, i2);

	test = 0;
	i = printf("printf:    %-4.*f\n", 40, test);
	i2 = ft_printf("ft_printf: %-4.*f\n", 40, test);
	printf("printf: %d    ft_printf: %d\n", i, i2);

	test = -0;
	i = printf("printf:    %-4.*f\n", 4, test);
	i2 = ft_printf("ft_printf: %-4.*f\n", 4, test);
	printf("printf: %d    ft_printf: %d\n", i, i2);

	test = -0;
	i = printf("printf:    %-4.f\n", -0.0);
	i2 = ft_printf("ft_printf: %-4.f\n", -0.0);
	printf("printf: %d    ft_printf: %d\n", i, i2);

	test = 0;
	i = printf("printf:    %-4.*f\n", 0.0);
	i2 = ft_printf("ft_printf: %-4.*f\n", 0.0);
	printf("printf: %d    ft_printf: %d\n", i, i2);



*/

//	i = printf(str21, 20, 20 ,20);
//	i2 = ft_printf(str21, 20, 20, 20);
//	printf("printf: %d    ft_printf: %d\n", i, i2);

//	i = printf(str2, -300000, 23);
//	i2 = ft_printf(str2, -300000, 23);
//	printf("printf: %d    ft_printf: %d\n", i, i2);
/*	
	i = printf("%20.9p\n", NULL);
	i2 = ft_printf("%20.9p\n", NULL);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf("%-020.9p\n", NULL);
	i2 = ft_printf("%-020.9p\n", NULL);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf("%020.9p\n", NULL);
	i2 = ft_printf("%020.9p\n", NULL);
	printf("printf: %d    ft_printf: %d\n", i, i2);
*/	/*
	i = printf("%04d...\n", -532);
	i2 = ft_printf("%04d...\n", -532);
	printf("printf: %d    ft_printf: %d\n", i, i2);

	i = printf(str3, 1, 0, -2222, -233);
	i2 = ft_printf(str3, 1, 0, -2222, -233);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf(str4, NULL, "aled", "dur");
	i2 = ft_printf(str4, NULL, "aled", "dur");
	printf("printf: %d    ft_printf: %d\n", i, i2);

	i = printf(str11, "testing testing", "dur");
	i2 = ft_printf(str11, "testing testing", "dur");
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	int *p = NULL;
	p = &i;

	i = printf(str6, -999, 6);
	i2 = ft_printf(str6, -999, 6);
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
	
	i = printf(str10, 'U', 'Q');
	i2 = ft_printf(str10, 'U', 'Q');
	printf("printf: %d    ft_printf: %d\n", i, i2);
*/	return (0);
}
