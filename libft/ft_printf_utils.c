/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchauvin <hchauvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:22:50 by hchauvin          #+#    #+#             */
/*   Updated: 2023/08/07 11:00:53 by hchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_percent(void)
{
	return (ft_printchar('%'));
}

int	ft_print_di(int a)
{
	int	len;

	len = 0;
	if (a == 0)
		return (ft_printchar('0'));
	if (a == -2147483648)
		return (ft_printstr("-2147483648"));
	if (a < 0)
	{
		len += ft_printchar('-');
		a *= -1;
	}
	if (a >= 10)
		len += ft_print_di(a / 10);
	write(1, &"0123456789"[a % 10], 1);
	return (len + 1);
}

int	ft_print_uns(unsigned int a)
{
	int	len;

	len = 0;
	if (a >= 10)
		len += ft_print_uns(a / 10);
	write(1, &"0123456789"[a % 10], 1);
	return (len + 1);
}

int	ft_print_ptr(unsigned long n, int ox)
{
	int	len;

	len = 0;
	if (!n)
		return (write(1, "(nil)", 5));
	if (ox == 1)
	{
		len += write(1, "0x", 2);
		ox = 0;
	}
	if (n >= 16)
		len += ft_print_ptr(n / 16, ox);
	write(1, &"0123456789abcdef"[n % 16], 1);
	return (len + 1);
}

int	ft_print_hex(unsigned int n, const char c)
{
	int	len;

	len = 0;
	if (n >= 16)
		len += ft_print_hex(n / 16, c);
	if (c == 'x')
		write(1, &"0123456789abcdef"[n % 16], 1);
	else if (c == 'X')
		write(1, &"0123456789ABCDEF"[n % 16], 1);
	return (len + 1);
}
