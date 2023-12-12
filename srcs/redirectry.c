/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:58:11 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/12 16:36:08 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_rediretion_error(t_data *data, t_token *token)
{
    if (!token->next)
    {
        printf("Myshell: syntax error near unexpected token `newline'\n");
        data->last_exit_status = 1;
        return (1);
    }
    else if(token->next->type != TK_TYPE_STR)
    {
        printf("Myshell: syntax error near unexpected token `%s'\n", token->next->val);
        data->last_exit_status = 1;
        return (1);
    }
    return (0);
}


int    apply_redirection_out_append(t_data *data, t_token *token)
{
    int     fd;

    if (ft_rediretion_error(data, token))
        return (1);
    fd = open(token->next->val, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        printf("Myshell: %s: %s\n", token->next->val, strerror(errno));
        data->last_exit_status = 1;
        return (1);
    }
    if (data->original_stdout == -1)
        data->original_stdout = dup(STDOUT_FILENO);
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        printf("Myshell: %s: %s\n", token->next->val, strerror(errno));
        data->last_exit_status = 1;
        close(fd);
        return (1);
    }
    data->current_stdout = fd;
    close(fd);
    return (0);
}

int    apply_redirection_out(t_data *data, t_token *token)
{
    int     fd;

    if (ft_rediretion_error(data, token))
        return (1);
    fd = open(token->next->val, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("Myshell: %s: %s\n", token->next->val, strerror(errno));
        data->last_exit_status = 1;
        return (1);
    }
    if (data->original_stdout == -1)
        data->original_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    data->current_stdout = fd;
    close(fd);
    return (0);
}

int    apply_redirections(t_data *data, t_token **tokens)
{
    t_token *tmp;
    int     ret;

    ret = 0;
    tmp = *tokens;
    while (tmp)
    {
        if (tmp->type == TK_TYPE_RED_OUT)
            ret = apply_redirection_out(data, tmp);
        else if (tmp->type == TK_TYPE_RED_OUT_APPEND)
        {
            if (data->current_stdout != STDOUT_FILENO && data->current_stdout != -1)
                close(data->current_stdout);
            ret = apply_redirection_out_append(data, tmp);
        }
        if (ret == 1)
            return (ret);
       /* if (tmp->type == TK_TYPE_RED_IN)
            apply_redirection_in(data, tmp);
        if (tmp->type == TK_TYPE_RED_IN_DELIM)
            apply_redirection_in_delim(data, tmp);*/
        tmp = tmp->next;
    }
    return (ret);
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