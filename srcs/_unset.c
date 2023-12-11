/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:16:55 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/11 08:54:46 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int ft_str_starts_with(char *str, char *start);
char **ft_tab_dup(char **tab);
void ft_free_tab(char **tab);
char **free_tab_and_return_null(char **tab);


int exec_unset(int argc, char **argv, t_data *data)
{
    int arg_id;
    int env_id;
    int switch_id;

    arg_id = 1;
    while (arg_id < argc)
    {
        env_id = 0;
        while (data->env[env_id])
        {
            if (ft_str_starts_with(data->env[env_id], argv[arg_id]))
            {
                free(data->env[env_id]);
                switch_id = env_id;
                while (data->env[switch_id])
                {
                    data->env[switch_id] = data->env[switch_id + 1];
                    switch_id++;
                }
            }
            env_id++;
        }
        arg_id++;
    }
    return (0);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int     main()
{
    char    *test_env[] = {"TEST=1", "TEST2=2", "TEST3=3", NULL};
    t_data  data;
    data.env = ft_tab_dup(test_env);

    int i = 0;
    printf("avant suppression de test2:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    char    *args1[] = {"unset", "TEST2", NULL};
    exec_unset(2, args1, &data);
    i = 0;
    printf("apres suppression de test2:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    i = 0;
    printf("avant suppression de test4 inexistante:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    char    *args2[] = {"unset", "TEST4", NULL};
    exec_unset(2, args2, &data);
    i = 0;
    printf("apres suppression de test4 inexistante:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    i = 0;
    printf("avant suppression de la 1ere variable:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    char    *args3[] = {"unset", "TEST", NULL};
    exec_unset(2, args3, &data);
    i = 0;
    printf("apres suppression de la 1ere variable:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    ft_free_tab(data.env);
    return (0);
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

char    **free_tab_and_return_null(char **tab)
{
    ft_free_tab(tab);
    return (NULL);
}

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
    new = (char **)calloc(i + 1, sizeof(char *));
    if (!new)
        return (NULL);
    j = 0;
    while (j < i)
    {
        new[j] = strdup(tab[j]);
        if (!new[j])
            return (free_tab_and_return_null(new));
        j++;
    }
    return (new);
}

int ft_str_starts_with(char *str, char *start)
{
    int i;

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
*/

