/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:22:23 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/05 18:24:11 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data    *init_data(char **env)
{
    t_data  *data;

    data = ft_calloc(1, sizeof(t_data));
    if (!data)
        exit(1);
    data->env = ft_tab_dup(env);
    data->line = NULL;
    data->exit = 0;
    data->last_exit_status = 0;
    data->stdin = dup(0);
    data->stdout = dup(1);
    data->tokens = NULL;
    return (data);
}