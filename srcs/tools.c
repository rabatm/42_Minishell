/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:10:14 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/07 08:15:26 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_is_white_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

char    *ft_strtrim_whitespace(const char *str)
{
    int     start;
    int     end;
    char    *trimmed;

    if (!str)
        return (NULL);
    start = 0;
    while (str[start] && ft_is_white_space(str[start]))
        start++;
    end = ft_strlen(str) - 1;
    while (end > start && ft_is_white_space(str[end]))
        end--;
    trimmed = ft_substr(str, start, end - start + 1);
    return (trimmed);
}