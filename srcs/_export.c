/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:17:27 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/08 18:35:53 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
char *extract_key_from_arg(char *arg)
{
    char *key;
    char *value;

    value = ft_strchr(arg, '=');
    if (value)
    {
        *value = '\0';
        key = ft_strdup(arg);
    }
    else
        key = ft_strdup(arg);
    return (key);
}

void    update_env(t_data *data, char *arg)
{
    char *key;
    char *value;
    int env_id;

    key = extract_key_from_arg(arg);
    value = ft_strchr(arg, '=');
    if (value)
        value++;
    if (!data || !data->env || !key || !arg)
        return ;
    env_id = 0;
    while (data->env[env_id])
    {
        if (ft_str_starts_with(data->env[env_id], key))
        {
            free(data->env[env_id]);
            data->env[env_id] = ft_strdup(arg);
            free(key);
            return ;
        }
        env_id++;
    }
    data->env = ft_add_str_to_tab(data, arg);
    data->env[env_id] = ft_strdup(arg);
    data->env[env_id + 1] = NULL;
    free(key);
}

int     exec_export(int argc, char **argv, t_data *data)
{
    int arg_id;

    if (!data || !data->env)
        return (0);
    arg_id = 1;
    while (arg_id < argc)
    {
        update_env(data, argv[arg_id]);
    }
    return (0);
}
*/


