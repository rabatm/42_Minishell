/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:58:11 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/12 13:50:15 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    apply_redirection_out_append(t_data *data, t_token *token)
{
    int     fd;

    fd = open(token->next->val, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        printf("Myshell: %s: %s\n", token->next->val, strerror(errno));
        data->last_exit_status = 1;
        return ;
    }
    if (data->original_stdout == -1)
        data->original_stdout = dup(STDOUT_FILENO);
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        printf("Myshell: %s: %s\n", token->next->val, strerror(errno));
        data->last_exit_status = 1;
        close(fd);
        return ;
    }
    data->current_stdout = fd;
    close(fd);
}

void    apply_redirection_out(t_data *data, t_token *token)
{
    int     fd;

    fd = open(token->next->val, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("Myshell: %s: %s\n", token->next->val, strerror(errno));
        data->last_exit_status = 1;
        return ;
    }
    if (data->original_stdout == -1)
        data->original_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    data->current_stdout = fd;
    close(fd);
}

void    apply_redirections(t_data *data, t_token **tokens)
{
    t_token *tmp;

    tmp = *tokens;
    while (tmp)
    {
        if (tmp->type == TK_TYPE_RED_OUT)
            apply_redirection_out(data, tmp);
        if (tmp->type == TK_TYPE_RED_OUT_APPEND)
        {
            if (data->current_stdout != STDOUT_FILENO && data->current_stdout != -1)
                close(data->current_stdout);
            apply_redirection_out_append(data, tmp);
        }
       /* if (tmp->type == TK_TYPE_RED_IN)
            apply_redirection_in(data, tmp);
        if (tmp->type == TK_TYPE_RED_IN_DELIM)
            apply_redirection_in_delim(data, tmp);*/
        tmp = tmp->next;
    }
}

void    reset_redirections(t_data *data)
{
    if (data->original_stdout != -1)
    {
        dup2(data->original_stdout, STDOUT_FILENO);
        close(data->original_stdout);
        data->original_stdout = -1;
    }
    if (data->original_stdin != -1)
    {
        dup2(data->original_stdin, STDIN_FILENO);
        close(data->original_stdin);
        data->original_stdin = -1;
    }
}