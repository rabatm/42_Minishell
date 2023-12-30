/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:39:29 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 16:29:10 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_x3(char *part1, char *part2, char *part3)
{
	char	*part12;
	char	*part123;

	part12 = ft_strjoin(part1, part2);
	part123 = ft_strjoin(part12, part3);
	free(part12);
	return (part123);
}

char	*ft_str_replace_version_3(char *str, char *new_val, int start, int end)
{
	char	*part1;
	char	*part3;
	char	*part123;

	if (!str)
		return (NULL);
	part1 = ft_substr(str, 0, start);
	part3 = ft_substr(str, end, ft_strlen(str) - end);
	if (new_val != NULL)
		part123 = ft_strjoin_x3(part1, new_val, part3);
	else
		part123 = ft_strjoin(part1, part3);
	free(part1);
	free(part3);
	return (part123);
}
