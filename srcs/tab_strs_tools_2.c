/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_strs_tools_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:03:33 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/05 17:24:49 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_str_starts_with(char *str, char *start)
{
    int i;

    i = 0;
    while (str[i] && start[i])
    {
        if (str[i] != start[i])
            return (0);
        i++;
    }
    if (start[i])
        return (0);
    return (1);
}

int ft_str_ends_with(char *str, char *end)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
        i++;
    while (end[j])
        j++;
    while (j >= 0)
    {
        if (str[i] != end[j])
            return (0);
        i--;
        j--;
    }
    return (1);
}

int ft_strs_equals(char *s1, char *s2)
{
    return (ft_strncmp(s1, s2, ft_strlen(s1) + 1) == 0);
}