/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:22:23 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/20 18:50:56 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
t_data    *init_data(char **env)
{
    t_data  *data;

    data = (t_data *)ft_calloc(1, sizeof(t_data));
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
*/

t_data    *init_data(char **env)
{
    t_data  *data;

    data = (t_data *)ft_calloc(1, sizeof(t_data));
    if (!data)
        exit(1);
    data->env = ft_tab_dup(env);
    data->line = NULL;
    data->exit = 0;
    data->last_exit_status = 0;
    data->current_stdin = STDIN_FILENO; // 0
    data->original_stdin = -1; // -1 = not set
    data->current_stdout = STDOUT_FILENO; // 1
    data->original_stdout = -1; // -1 = not set
    data->tokens = NULL;
    data->heredoc_handled = 0;
    data->nb_pipes = 0;
    return (data);
}

void    free_data(t_data *data)
{
    if (!data)
        return ;
    if (data->env)
        ft_free_tab(data->env);
    //if (data->line)
    //   free(data->line);
    if (data->tokens)
        free_tokens(data->tokens);
    free(data);
}