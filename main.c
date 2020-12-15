/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:20:00 by rsanchez          #+#    #+#             */
/*   Updated: 2020/12/15 14:22:23 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int ft_printf(const char *str, ...);

int main(void)
{
	char *str = "Classique///Coucou bande de nouillf\n";
//	char *str2 = "INT///Coucou bande %0-10.6i nouille %010.6f\n";
	char *str20 = "hi low";
	char *str21 = "INT///Coucou bande %0-10.6i nouille %010.6f\n";
/*	char *str22 = "INT///Coucou bande %0-10.6i nouille %010.6f\n";
	char *str3 = "HEuA///Coucou bande %-20.0x nouille %-10f\n";
	char *str4 = "STRING///Coucou bande %s %s\n";
	char *str11 = "%s";
	char *str5 = "ADDRESS///Coucou bande %-f\n";
	char *str7 = "ADDRESS///Coucou bande %-2f\n";
	char *str8 = "ADDRESS///Coucou bande %-1f\n";
	char *str9 = "ADDRESS///Coucou bande %-20.20f\n";
	char *str10 = "char///Couco%-2c ban%%de de %3c\n";
	char *str6 = "UNSIGNEDINT///Coucou %-.0ubande %-10f\n";

	i = printf("%*i, %*d, %*d, %*d, %*d, %*d, %*u, %*x, %*f\n", a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0);
	i2 = ft_printf("%*i, %*d, %*d, %*d, %*d, %*d, %*u, %*x, %*f\n", a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0, a, 0);
		
	printf("printf: %d    ft_printf: %d\n", i, i2);
*/
#include <math.h>
#include <wchar.h>
#include <locale.h>

    setlocale(LC_ALL, "");
	wchar_t truc[] = {'è','ù','é','ô', 0};
	wchar_t truc2 = 'è';
	int	i = -2.9999999;
	int	i2 = -2.40;
unsigned long teterere = 42;	
printf("printf \t| decimal \t| %%0o | %020d bonjour %20-0d\n", teterere, 15);

	       i = ft_printf("printf c:    %#-20.5b\n", -512);
	       i = ft_printf("printf c:    %+20.5b\n", 512);
	       i = ft_printf("printf c:    % 20.5b\n", 512);
	       i = ft_printf("printf c:    %0 20.5b\n", 512);
	       i = ft_printf("printf c:    %+ 20.5b\n", 512);
	       i = ft_printf("printf c:    %- 20.5b\n", 512);
	       i = ft_printf("printf c:    %0-+20.5b\n", 512);
	       i = ft_printf("printf c:    %20.5b\n", 512);
	       i = ft_printf("printf c:    %20.5b\n", 512);
	i2 = ft_printf("ft_printf c: %lc\n", 512);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
               i = printf("printf c:    %ls\n", truc);
	i2 = ft_printf("ft_printf c: %ls\n", truc);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
               
	       i = printf("printf c:    %ls\n", L"ο Δικαιοπολις εν αγρω εστιν");
	i2 = ft_printf("ft_printf c: %ls\n", L"ο Δικαιοπολις εν αγρω εστιν");
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	    i = printf("printf:    %+ 050.100s\n", str);
	i2 = ft_printf("ft_printf: %+ 050.100s\n", str);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
		
	    i = printf("printf c:    %- 050.100c\n", '\0');
	i2 = ft_printf("ft_printf c: %- 050.100c\n", '\0');
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
		
	    i = printf("printf %:    %+ 050.100%\n", str);
	i2 = ft_printf("ft_printf %: %+ 050.100%\n", str);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
		
	double test = -1291;
	    i = printf("printf:    %i\n", test);
	i2 = ft_printf("ft_printf: %i\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 0.0894255;
	    i = printf("printf:    %g\n", test);
	i2 = ft_printf("ft_printf: %g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = -0.00032;
	    i = printf("printf:    %.1g\n", test);
	i2 = ft_printf("ft_printf: %.1g\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	test = 0.87650894255;

	test = 198;
	    i = printf("printf:    % -4.4f\n", test);
	i2 = ft_printf("ft_printf: % -4.4f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	test = 0.87650894255;

	i = printf("printf:    %-20.35f\n", test);
	i2 = ft_printf("ft_printf: %-20.35f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 0.87650894255;
	    i = printf("printf:    %-20.10f\n", test);
	i2 = ft_printf("ft_printf: %-20.10f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 3.001;
	    i = printf("printf:    %-4.3f\n", test);
	i2 = ft_printf("ft_printf: %-4.3f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 3.601;
	    i = printf("printf:    %-4.4f\n", test);
	i2 = ft_printf("ft_printf: %-4.4f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 3.601;
	    i = printf("printf:    %-4.*f\n", 8, test);
	i2 = ft_printf("ft_printf: %-4.*f\n", 8, test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 1.20026416000;
	    i = printf("printf:    %-4.*f\n", 8, test);
	i2 = ft_printf("ft_printf: %-4.*f\n", 8, test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 0.600013;
	    i = printf("printf:    %-4.4f\n", test);
	i2 = ft_printf("ft_printf: %-4.4f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 0.6000001367;
	    i = printf("printf:    %-4f\n", test);
	i2 = ft_printf("ft_printf: %-4f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 3.0;
	    i = printf("printf:    %-4.2f\n", test);
	i2 = ft_printf("ft_printf: %-4.2f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 3.00030003000300025;
	    i = printf("printf:    %-4.16f\n", test);
	i2 = ft_printf("ft_printf: %-4.16f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 1000000000000000000000.2;
	    i = printf("printf:    %.1f\n", test);
	i2 = ft_printf("ft_printf: %.1f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 9999999999999999.2;
	    i = printf("printf:    %.1f\n", test);
	i2 = ft_printf("ft_printf: %.1f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

test = -1797693134862315708145418276846754670.88889;
//	test = 555555555555222222222222222222222222222222222222222299999999999999999999999999999999999999999999999999999999999999.2;
	    i = printf("printf:    %f\n", test);
	i2 = ft_printf("ft_printf: %f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = -3.6004;
	    i = printf("printf:    %-4.3f\n", test);
	i2 = ft_printf("ft_printf: %-4.3f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = -5.7848744;
	    i = printf("printf:    %+11.*f\n", -1, test);
	i2 = ft_printf("ft_printf: %+11.*f\n", -1, test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 222.50000;
	    i = printf("printf:    % 20.10f\n", test);
	i2 = ft_printf("ft_printf: % 20.10f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 223.50000;
	    i = printf("printf:    %-15.8f\n", test);
	i2 = ft_printf("ft_printf: %-15.8f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 0.000000;
	    i = printf("printf:    %  #.f\n", test);
	i2 = ft_printf("ft_printf: %  #.f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = -0.500000;
	    i = printf("printf:    %#010.f\n", test);
	i2 = ft_printf("ft_printf: %#010.f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);

	test = 303.37647788;
	    i = printf("printf:    %# 10.5f\n", test);
	i2 = ft_printf("ft_printf: %# 10.5f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 3444444444444403.37647788;
	    i = printf("printf:    %-4.4f\n", test);
	i2 = ft_printf("ft_printf: %-4.4f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 303.376477444488;
	    i = printf("printf:    %# 4.4f\n", test);
	i2 = ft_printf("ft_printf: %# 4.4f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 123.12345584846516545525555525555550000000000000000000000000000000000000000000000000000000000000000000;
	    i = printf("printf:    %#-4.20f\n", test);
	i2 = ft_printf("ft_printf: %#-4.20f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 123.123455464161641654651616516146468500000000000000000000000000000000000000000000000000;
	    i = printf("printf:    %#-4.20f\n", test);
	i2 = ft_printf("ft_printf: %#-4.20f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 123.1234550000000000000004684165165146516164646410000000000000000000000000000000000000000000000000000;
	    i = printf("printf:    %#-4.20f\n", test);
	i2 = ft_printf("ft_printf: %#-4.20f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 123.1234550000000000641654684516541515000000000000000000000000000000000000000000000000000000000;
	    i = printf("printf:    %#-4.20f\n", test);
	i2 = ft_printf("ft_printf: %#-4.20f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 123.1234550000000006465415616515150000000000000000000000000000000000000000000000000000000000;
	    i = printf("printf:    %#-4.20f\n", test);
	i2 = ft_printf("ft_printf: %#-4.20f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
	
	test = 123.12345500000006065465156165165146515600000000000000000000000000000000000000000000000000000000000;
	    i = printf("printf:    %#-4.20f\n", test);
	i2 = ft_printf("ft_printf: %#-4.20f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
/*	
	test = 5.55555;
	int test3 = 4.55555;
	int test2 = test - 0.10000;
	int test4 = (test * 10 - 1) / 10;
	    i = printf("printf:    %#-4.20f\n", test);
	    i = printf("printf:    %#-4.20f\n", test3);
	    i = printf("printf:    %#-4.20f\n", test2);
	    i = printf("printf:    %020.10f\n", test4);
	i2 = ft_printf("ft_printf: %020.10f\n", test);
	printf("printf: %d    ft_printf: %d\n\n", i, i2);
*/	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
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
	i = printf("%20.9f\n", NULL);
	i2 = ft_printf("%20.9f\n", NULL);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf("%-020.9f\n", NULL);
	i2 = ft_printf("%-020.9f\n", NULL);
	printf("printf: %d    ft_printf: %d\n", i, i2);
	
	i = printf("%020.9f\n", NULL);
	i2 = ft_printf("%020.9f\n", NULL);
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
