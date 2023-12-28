/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erreur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:33:59 by mrabat            #+#    #+#             */
/*   Updated: 2023/12/11 17:00:25 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_check_file_exist(char *fd)
{
	int result;
	result = access(fd, R_OK);
	return (result);
}

int ft_arg_error(char **argv)
{
	if (ft_check_file_exist(argv[1]))
	{
		ft_putstr_fd("FILE INPUT NOT EXIST",2);
		return (1);
	}
	if (!ft_check_file_exist(argv[4]))
	{
		ft_putstr_fd("FILE OUPUT EXIST",2);
		return (1);
	}
	return (0);
}