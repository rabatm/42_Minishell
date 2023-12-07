/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 06:12:02 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/07 14:54:53 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int     get_and_or_type(char *line, int i)
{
    if (line[i] == '|')
    {
        if (line[i + 1] == '|')
            return (TK_TYPE_OR);
        else
            return (TK_TYPE_PIPE);
    }
    else if (line[i] == '&')
    {
        if (line[i + 1] == '&')
            return (TK_TYPE_AND);
        else
            return (TK_TYPE_STR);
    }
    return (0);
}


int     get_redirection_type(char *line, int i)
{
    if (line[i] == '>')
    {
        if (line[i + 1] == '>')
            return (TK_TYPE_RED_OUT_APPEND);
        else
            return (TK_TYPE_RED_OUT);
    }
    else if (line[i] == '<')
    {
        if (line[i + 1] == '<')
            return (TK_TYPE_RED_IN_DELIM);
        else
            return (TK_TYPE_RED_IN);
    }
    return (0);
}


int     get_token_type(char *line, int i)
{
    if (line[i] == '|' || line[i] == '&')
        return (get_and_or_type(line, i));
    else if (line[i] == '>' || line[i] == '<')
        return (get_redirection_type(line, i));
    else if (line[i] == '(')
        return (TK_TYPE_PAR_O);
    else if (line[i] == ')')
        return (TK_TYPE_PAR_C);
    return (0);
}

/*
    opening_quote_id ; position de la quote ouvrante
    return: position de la quote fermante
*/
int    get_id_of_closing_quote(char *line, int opening_quote_id)
{
    opening_quote_id ++;
    while (line[opening_quote_id])
    {
        if (line[opening_quote_id] == '\'')
            return opening_quote_id;
        opening_quote_id++;
    }
    return (-1);
}

int    get_id_of_closing_dquote(char *line, int opening_quote_id)
{
    opening_quote_id ++;
    while (line[opening_quote_id])
    {
        if (line[opening_quote_id] == '"')
            return opening_quote_id;
        opening_quote_id++;
    }
    return (-1);
}

int     get_end_str_id(char *line, int start_str_id)
{
    start_str_id ++;

    while (line[start_str_id] && !ft_is_white_space(line[start_str_id]) && (line[start_str_id] != '&'
    || line[start_str_id] != '|' || line[start_str_id] != '>'
    || line[start_str_id] != '<' || line[start_str_id] != '"'
    || line[start_str_id] != '\''|| line[start_str_id] != '$'))
        start_str_id++;
    return (start_str_id);

}



t_token     **tokenize_line(char *line)
{
    t_token     **tokens;
    int         i;
    int         type;
    char    *val;
   // int     j;

    tokens = (t_token **)ft_calloc(1, sizeof(t_token *));
    if (!tokens)
        return (NULL);
    i = 0;
    while (line[i])
    {
        if (ft_is_white_space(line[i]))
            i++;
        else if (line[i] == '&' || line[i] == '|' || line[i] == '>' || line[i] == '<')
        {
            if (line[i + 1] == line[i])
            {
                //printf("value:%c%c, type=OPx2\n", line[i] ,line[i] );
                type = get_token_type(line, i);
                val = ft_substr(line, i, 2);
                //*tokens = create_new_token(val, type);
                make_list_tokens(tokens, val, type);
                i+=2;
            }
            else
            {
                //printf("value:%c , type=OPx1\n", line[i]  );
                type = get_token_type(line, i);
                val = ft_substr(line, i, 1);
                //*tokens = create_new_token(val, type);
                make_list_tokens(tokens, val, type);
                i+=1;
            }
        }
        else if (line[i] == '"')
        {
            int closing_quote_id =  get_id_of_closing_dquote(line , i);
            if (closing_quote_id == -1)
            {
                printf("error\n");
                return (NULL);
            }
            val = ft_substr(line, i + 1, closing_quote_id - i - 1);
            //printf("value:%s,  type=TK_TYPE_STR\n", val);
            type = TK_TYPE_STR;
            //(*tokens)->escape_env_var = 0;
            //*tokens = create_new_token(val, type);
            make_list_tokens(tokens, val, type);
            (*tokens)->escape_env_var = 0;
           // token.escape_env_var= false // on remplacera les env_var
            i = closing_quote_id + 1;
        }
        else if (line[i] == '\'')
        {
            int closing_quote_id =  get_id_of_closing_quote(line , i);
                //printf("closing_quote_id = %d\n", closing_quote_id);

            if (closing_quote_id == -1)
            {
                printf("error\n");
                return (NULL);
            }
            val = ft_substr(line, i + 1, closing_quote_id - i - 1);
            type = TK_TYPE_STR;
            //*tokens = create_new_token(val, type);
            make_list_tokens(tokens, val, type);
            (*tokens)->escape_env_var = 1;
            //printf("value:%s,  type=TK_TYPE_STR\n", val);
            //token.type = TK_TYPE_STR

           // token.escape_env_var= true // on NE remplacera PAS les env_var
            i = closing_quote_id + 1;
        }
        else
        {
            int end_str_id = get_end_str_id(line, i);
            val = ft_substr(line, i, end_str_id - i);
            type = TK_TYPE_STR;
            //*tokens = create_new_token(val, type);
            make_list_tokens(tokens, val, type);
            (*tokens)->escape_env_var = 0;
            //printf("value:%s,  type=TK_TYPE_STR\n", val);
            i = end_str_id;
            //token.type = TK_TYPE_STR
            //i++; // en attendant de faire simple quote et nor
        }


    }
    return (tokens);
}