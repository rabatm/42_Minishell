/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 06:12:02 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/07 08:14:28 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     get_and_or_type(char *line, int *i)
{
    if (line[*i] == '|')
    {
        if (line[*i + 1] == '|')
        {
            (*i)++;
            return (TK_TYPE_OR);
        }
        return (TK_TYPE_PIPE);
    }
    else if (line[*i] == '&')
    {
        if (line[*i + 1] == '&')
        {
            (*i)++;
            return (TK_TYPE_AND);
        }
      // ??????  return (TK_TYPE_STR);
    }
    return (0);
}


int     get_redirection_type(char *line, int *i)
{
    if (line[*i] == '>')
    {
        if (line[*i + 1] == '>')
        {
            (*i)++;
            return (TK_TYPE_RED_OUT_APPEND);
        }
        return (TK_TYPE_RED_OUT);
    }
    else if (line[*i] == '<')
    {
        if (line[*i + 1] == '<')
        {
            (*i)++;
            return (TK_TYPE_RED_IN_DELIM);
        }
        return (TK_TYPE_RED_IN);
    }
    return (0);
}

int     get_token_type(char *line, int *i)
{
    if (line[*i] == '|' || line[*i] == '&')
        return (get_and_or_type(line, i));
    else if (line[*i] == '>' || line[*i] == '<')
        return (get_redirection_type(line, i));
    else if (line[*i] == '(')
        return (TK_TYPE_PAR_O);
    else if (line[*i] == ')')
        return (TK_TYPE_PAR_C);
    else if (line[*i] == '\'')
        return (TK_TYPE_QUOTE);
    else if (line[*i] == '"')
       return (TK_TYPE_DQUOTE);
    else if (line[*i] == '\0') // est ce utilie ?
        return (TK_TYPE_END);
    else
        return (TK_TYPE_STR);
}
//va falloir modifier pour gerer les erreurs (pas de quote fermante, etc...)

char     *get_token_value(char *line, int *i, int type)
{
    char    *val;
    int     j;

    j = 0;
    val = NULL;
    val = ft_calloc(1, sizeof(char));
    if (type == TK_TYPE_QUOTE)
    {
        (*i)++;
        while (line[*i] && line[*i] != '\'')
        {
            val[j] = line[*i];
            (*i)++;
            j++;
        }
        (*i)++;
    }
    else if (type == TK_TYPE_DQUOTE)
    {
        (*i)++;
        while (line[*i] && line[*i] != '"')
        {
            val[j] = line[*i];
            (*i)++;
            j++;
        }
        (*i)++;
    }
    else if (type == TK_TYPE_STR)
    {
        while (line[*i] && !ft_is_white_space(line[*i]) && line[*i] != '|'
        && line[*i] != '&' && line[*i] != '>' && line[*i] != '<'
        && line[*i] != '(' && line[*i] != ')')
        {
            val[j] = line[*i];
            (*i)++;
            j++;
        }
    }
    return (val);
}


t_token     **tokenize_line(char *line)
{
    t_token     **tokens;
    int         i;
    int         type;
    char    *val;
   // int     j;

    tokens = ft_calloc(1, sizeof(t_token *));
    if (!tokens)
        exit(1);
    i = 0;
    while (line[i])
    {
        type = 0;
        if (ft_is_white_space(line[i]))
            i++;
        type = get_token_type(line, &i);
        val = get_token_value(line, &i, type);
        if (!make_list_tokens(tokens, val, type))
            return (NULL);
    }
    return (tokens);
}