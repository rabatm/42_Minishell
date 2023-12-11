/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:17:27 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/11 14:58:38 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *extract_key_from_arg(char *arg)
{
    char *key; // key = arg before '='
    char *value; // value = arg after '='
    char    *copy; // copy of arg

    copy = ft_strdup(arg);
    if (!copy)
        return (NULL);
    value = ft_strchr(copy, '=');
    if (value)
    {
        *value = '\0'; // set '=' to '\0'
        key = ft_strdup(copy);
        *value = '='; // set '=' back to '='
    }
    else
        key = ft_strdup(copy); // key = arg
    return (key);
}

void    add_new_env_var(t_data *data, char *arg)
{
    int     env_id;

    env_id = 0;
    while (data->env[env_id]) // count env vars
        env_id++;
    data->env = ft_add_str_to_tab(data, arg); // add new env var
    data->env[env_id] = ft_strdup(arg); // duplicate arg
    if (!data->env[env_id])
        return ;
    data->env[env_id + 1] = NULL; // set next env var to NULL
}

int     update_existing_var(t_data *data, char *arg, char *key, char *update_value)
{
    int env_id;

    env_id = 0;
    while (data->env[env_id])
    {
        if (ft_str_starts_with(data->env[env_id], key)) // if key exists
        {
            if (update_value) //if value exist , update it
            {
                free(data->env[env_id]);
                data->env[env_id] = ft_strdup(arg);
            }
            return (1); // return 1 if key exists
        }
        env_id++;
    }
    return (0); // return 0 if key doesn't exist
}

void    update_env(t_data *data, char *arg)
{
    char *key; // key = arg before '='
    char *value; // value = arg after '='
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
    updated = update_existing_var(data, arg, key, value); // if key exists, update it
    if (!updated)
        add_new_env_var(data, arg); // else, add it
    free(key);
}

int     exec_export(int argc, char **argv, t_data *data)
{
    int arg_id;
    int i;

    if (!data || !data->env)
        return (0);
    if (argc == 1) // if no args, print all env vars
    {
        i = 0;
        while (data->env[i])
        {
            ft_printf("export %s\n", data->env[i]);
            i++;
        }
    }
    else // else, update env vars
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
