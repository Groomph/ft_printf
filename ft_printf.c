/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/11/14 15:31:47 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int ft_printf_parsing(char *str, va_list *param, int *count);

/*
typedef struct	s_pars
{
		int precision_bool = 0;
		int precision_val = 0;
		int field_width_val = 0;
		char convert_char;
		char *todisplay;
}		t_pars;

char	*my_itoa(int nb);
char	*tohexa(int nb);
char	*my_strcpy(char *str);


int	my_atoi(char *str, int *i)
{
	unsigned int	nb;

	nb = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		nb *= 10;
		nb += (str[*i] - '0');
		(*i)++;
	}
	return (nb);
}

char	*convert(t_pars *pars, va_list *param)
{
	if (pars->convert_char == 's')
		return (my_strcpy(va_arg(*param, char*)));
	if (pars->convert_char == 'x')
		return (tohexa(va_arg(*param, unsigned int)));
	if (pars->convert_char == 'd')
		return (my_itoa(va_arg(*param, int)));
	
}

int	display(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		write(1, &str[i++], 1);
	return (i);
}

int	ft_parsing(char *str, t_pars *pars, int *i)
{
	if (str[*i] >= 1 && str[*] <= 9)
	{
		pars->field_witdh_value = my_atoi(str, i);
	}
	else if (str[*i] == '.')
	{
		pars->precision = my_atoi(str, i);
		pars->precision_bool = 1;
	}
	else if (str[*i] == 's' || str [*i] == 'd' || str[*i] == 'x')
	{
		pars->convert_char = str[(*i)++];
		return (1);
	}
	else
		return (0);
	return (ft_parsing(str, pars, i));
}

int	parsing_display(char *str, va_list *param, int *count)
{
	int	i;
	t_pars	*pars;

	if (!(pars = malloc(sizeof(t_pars))))
		return (0);
	i = 0;
	//if (str[i] == '0')              ERROR to handle
	if (!ft_parsing(str, pars, &i))
		return (0);
	pars->todisplay = convert(pars, param);
	*count += display(pars->todisplay);
	free(pars->todisplay);
	free(pars);
	return (i);
}
*/

//   utiliser un buffeur plutot que malloc
int	ft_printf(const char *str, ...)
{
	int	i;
	va_list	param;
	int	count;
	
	i = 0;
	count = 0;
	va_start(param, str);
	while (str[i])
	{
		if (str[i] == '%')
			i += ft_printf_parsing((char*)&str[i], &param, &count);
	
	//	write(1, "test1", 5);
		write(1, &str[i], 1);
		i++;
		count++;
	}
	va_end(param);
	return (count);
}
