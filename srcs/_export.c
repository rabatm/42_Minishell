/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:17:27 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/21 12:28:44 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *extract_key_from_arg(char *arg)
{
    char *key;
    char *value;
    char    *copy;

    copy = ft_strdup(arg);
    if (!copy)
        return (NULL);
    value = ft_strchr(copy, '=');
    if (value)
    {
        *value = '\0';
        key = ft_strdup(copy);
        *value = '=';
    }
    else
        key = ft_strdup(copy);
    return (key);
}

void    add_new_env_var(t_data *data, char *arg)
{
    int     env_id;

    env_id = 0;
    while (data->env[env_id])
        env_id++;
    data->env = ft_add_str_to_tab(data, arg);
    data->env[env_id] = ft_strdup(arg);
    if (!data->env[env_id])
        return ;
    data->env[env_id + 1] = NULL;
}

int     update_existing_var(t_data *data, char *arg, char *key, char *update_value)
{
    int env_id;

    env_id = 0;
    while (data->env[env_id])
    {
        if (ft_str_starts_with(data->env[env_id], key))
        {
            if (update_value)
            {
                free(data->env[env_id]);
                data->env[env_id] = ft_strdup(arg);
            }
            return (1);
        }
        env_id++;
    }
    return (0);
}

void    update_env(t_data *data, char *arg)
{
    char *key;
    char *value;
    int updated;

    key = extract_key_from_arg(arg);
    value = ft_strchr(arg, '=');
    if (value)
        value++;
    if (!data || !data->env || !key || !arg)
    {
        free(key);
        return ;
    }
    updated = update_existing_var(data, arg, key, value);
    if (!updated)
        add_new_env_var(data, arg);
    free(key);
}

int     exec_export(int argc, char **argv, t_data *data)
{
    int arg_id;
    int i;

    if (!data || !data->env)
        return (0);
    sort_env(data);
    if (argc == 1)
    {
        i = 0;
        while (data->env[i])
        {
            printf("declare -x %s\n", data->env[i]);
            i++;
        }
    }
    else
    {
        arg_id = 1;
        while (arg_id < argc)
        {
            update_env(data, argv[arg_id]);
            arg_id++;
        }
    }
    return (0);
}
