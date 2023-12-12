/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:24:31 by hchauvin          #+#    #+#             */
/*   Updated: 2023/12/12 15:23:04 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_err(char *msg, int option)
{
	if (!msg)
		return (-1);
	printf("%s\n", msg);
	if (option == 0)
		return (0);
	exit (0);
}
