/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 06:13:24 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/07 08:25:40 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        free_tokens(t_token **tokens)
{
    t_token    *tmp;

    tmp = *tokens;
    if (!tokens || !*tokens)
        return ;
    while (tmp)
    {
        *tokens = tmp->next;
        free(tmp);
        tmp = *tokens;
    }
    free(tokens);
}

void		add_token(t_token **tokens, t_token *new_token)
{
    t_token	*last_token;

    if (!tokens || !new_token)
        return ;
    if (!*tokens)
    {
        *tokens = new_token;
        return ;
    }
    last_token = *tokens;
    while (last_token->next)
        last_token = last_token->next;
    last_token->next = new_token;
    new_token->previous = last_token;
}

t_token	*create_new_token(char *str, int type)
{
    t_token	*new_token;

    (void)str;
    new_token = ft_calloc(1, sizeof(t_token));
    if (!new_token)
        exit(1);
    new_token->type = type;
    new_token->val = ft_strdup(str);
    new_token->val = NULL;
    new_token->previous = NULL;
    new_token->next = NULL;

    return (new_token);
}

int     make_list_tokens(t_token **tokens, char *line, int type)
{
    t_token    *new_token;

    new_token = create_new_token(line, type);
    if (!new_token)
    {
        free(line);
        free_tokens(&new_token);
        return (0);
    }
    add_token(tokens, new_token);
    return (1);
}


