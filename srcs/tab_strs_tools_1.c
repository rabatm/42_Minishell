/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_strs_tools_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:02:53 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/08 11:57:14 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **ft_tab_dup(char **tab)
{
    char    **new;
    int     i;
    int     j;

    if (!tab)
        return (NULL);
    i = 0;
    while (tab[i])
        i++;
    new = ft_calloc(i + 1, sizeof(char *));
    if (!new)
        return (NULL);
    j = 0;
    while (j < i)
    {
        new[j] = ft_strdup(tab[j]);
        if (!new[j])
        {
            ft_free_tab(new);
            return (NULL);
        }
        j++;
    }
    return (new);
}

int ft_tab_size(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

void ft_free_tab(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return ;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void ft_print_tab(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return ;
    while (tab[i])
    {
        ft_printf("%s\n", tab[i]);
        i++;
    }
}

char    *ft_str_replace(char *str, char *new, int start, int end)
{
    char    *new_str;
    int     len_new;
    int     len_str;

    if (!str || !new || start < 0 || end < 0 || start > end)
        return (NULL);
    len_new = ft_strlen(new);
    len_str = ft_strlen(str);
    new_str = ft_calloc(len_str + len_new - (end - start) + 1, sizeof(char));
    if (!new_str)
        return (NULL);
    ft_memcpy(new_str, str, start);
    ft_memcpy(new_str + start, new, len_new);
    ft_strlcpy(new_str + start + len_new, str + end, len_str - end + 1);
    return (new_str);
}
