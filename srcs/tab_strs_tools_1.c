/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_strs_tools_ 1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:02:53 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/05 17:11:00 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **ft_tab_dup(char **tab)
{
    char    **new;
    int     i;

    i = 0;
    while (tab[i])
        i++;
    new = ft_calloc(i + 1, sizeof(char *));
    if (!new)
        return (NULL);
    i = 0;
    while (tab[i])
    {
        new[i] = ft_strdup(tab[i]);
        if (!new[i])
            return (NULL);
        i++;
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

int ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return (1);
}

