/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchauvin <hchauvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:39:28 by hchauvin          #+#    #+#             */
/*   Updated: 2023/08/07 10:56:47 by hchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstrlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		ft_printchar(str[len]);
		len++;
	}
	return (len);
}

int	ft_printstr(char *str)
{
	if (!str)
	{
		ft_putstrlen("(null)");
		return (6);
	}
	return (ft_putstrlen(str));
}

int	ft_verif(va_list args, const char format)
{
	int	return_value;
	int	ox;

	ox = 1;
	return_value = 0;
	if (format == 'c')
		return_value += ft_printchar(va_arg(args, int));
	else if (format == 's')
		return_value += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		return_value += ft_print_ptr((unsigned long)va_arg(args, void *), ox);
	else if (format == 'd' || format == 'i')
		return_value += ft_print_di(va_arg(args, int));
	else if (format == 'u')
		return_value += ft_print_uns(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		return_value += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		return_value += ft_print_percent();
	else
		return (0);
	return (return_value);
}

int	ft_printf(const char *format, ...)
{
	int		return_value;
	int		i;
	va_list	args;

	i = 0;
	return_value = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			return_value += ft_verif(args, format[i + 1]);
			i += 2;
		}
		else
			return_value += ft_printchar(format[i++]);
	}
	va_end(args);
	return (return_value);
}
