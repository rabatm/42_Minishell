/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:10:14 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/20 12:03:20 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_is_white_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n')
        return (1);
    return (0);
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

int	ft_tokensize(t_token **lst)
{
	t_token	*tmp;
	int		count;

	tmp = *lst;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
        if (tmp && tmp->type != TK_TYPE_RED_IN && tmp->type != TK_TYPE_RED_OUT && tmp->type != TK_TYPE_RED_OUT_APPEND)
		    count++;
	}
	return (count);
}