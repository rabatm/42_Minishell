/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_strs_tools_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:03:33 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 16:18:32 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_str_starts_with(char *str, char *start)
{
	int	i;

	if (!str || !start)
		return (0);
	if (!str[0] && !start[0])
		return (1);
	i = 0;
	while (str[i] && start[i])
	{
		if (str[i] != start[i])
			return (0);
		i++;
	}
	return (!start[i]);
}

int	ft_str_ends_with(char *str, char *end)
{
	int		len_str;
	int		len_end;

	if (!str || !end)
		return (0);
	len_str = ft_strlen(str);
	len_end = ft_strlen(end);
	return (len_str >= len_end
		&& ft_strs_equals(str + len_str - len_end, end));
}

int	ft_strs_equals(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	return (ft_strcmp(s1, s2) == 0);
}
