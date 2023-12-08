/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:16:55 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/08 18:17:08 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exec_unset(int argc, char **argv, char **env, t_data *data)
{
    int arg_id;
    int env_id;
    int switch_id;

    (void)env;
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