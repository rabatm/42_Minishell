/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_strs_tools_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:02:53 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/21 12:30:03 by svanmarc         ###   ########.fr       */
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
    new = (char **)ft_calloc(i + 1, sizeof(char *));
    if (!new)
        return (NULL);
    j = 0;
    while (j < i)
    {
        new[j] = ft_strdup(tab[j]);
        if (!new[j])
            return (free_tab_and_return_null(new));
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
    while (tab[i] != NULL)
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
        printf("%s\n", tab[i]);
        i++;
    }
}