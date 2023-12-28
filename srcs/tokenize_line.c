/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 06:12:02 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/28 17:04:22 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    make_op_token_and_return_id(char *line, int i, t_token **tokens)
{
    int type;
    char *val;
    int op_id;

    op_id = i;
    if (line[op_id + 1] == line[op_id])
    {
        type = get_token_type(line, op_id);
        val = ft_substr(line, op_id, 2);
        make_list_tokens(tokens, val, type, 0);
        op_id += 2;
    }
    else
    {
        type = get_token_type(line, op_id);
        val = ft_substr(line, op_id, 1);
        make_list_tokens(tokens, val, type, 0);
        if ((*tokens)->type == TK_TYPE_PIPE)
        op_id += 1;
    }
    return (op_id);
}
int     make_quote_token_and_return_id(char *line, int i, t_token **tokens)
{
    int closing_quote_id;
    char *val;
    int type;
    t_token *tmp;
    char quote_type;

    quote_type = line[i];
    tmp = NULL;
    closing_quote_id =  get_id_of_closing_quote(line , i);
    if (closing_quote_id == -1)
    {
        printf("don't forget to close the quote [%c]\n", quote_type);
        free_tokens(tokens);
        return (-1);
    }
    val = ft_substr(line, i + 1, closing_quote_id - i - 1);
    type = TK_TYPE_STR;
    make_list_tokens(tokens, val, type, 0);
    tmp = its_last_token(tokens);
    if (quote_type == '"')
        tmp->change_env_var = 0;
    else if (quote_type == '\'')
        tmp->change_env_var = 1;
    return (closing_quote_id + 1);
}





int     make_str_token_and_return_id(char *line, int i, t_token **tokens)
{
    int end_str_id;
    char *val;
    int type;
    int space_before;

    if (i > 0 && ft_is_white_space(line[i - 1]))
        space_before = 1;
    else
        space_before = 0;
    printf("debut   :  %c      ****     ", line[i]);
    end_str_id = get_end_str_id(line, i);
    printf("fin  :  %c\n", line[end_str_id -1]);
    val = ft_substr(line, i, end_str_id - i);
    type = TK_TYPE_STR;
    make_list_tokens(tokens, val, type, space_before);
    return (end_str_id);
}

t_token     **tokenize_line(char *line)
{
    t_token     **tokens;
    int         i;

    tokens = (t_token **)ft_calloc(1, sizeof(t_token *));
    if (!tokens)
        return (NULL);
    i = 0;
    while (line[i])
    {
        if (ft_is_white_space(line[i]))
            i++;
        else if (line[i] == '&' || line[i] == '|' || line[i] == '>' || line[i] == '<')
            i = make_op_token_and_return_id(line, i, tokens);
        else if (line[i] == '"' || line[i] == '\'')
        {
            i = make_quote_token_and_return_id(line, i, tokens);
            if (i == -1)
                return (NULL);
        }
        else
            i = make_str_token_and_return_id(line, i, tokens);
    }
   // merge_tokens_if_no_space_before(tokens);
    return (tokens);
}




/*




token
    space_before



parcourir line

	if is_white_space(current_char)
		current_char++


	else if current_char est dans "&|><"
		regarder si le char d'apres est identique ( >> ou << ou && ou ||)
		creer un token avec 1 OU 2 char 
            et definir son type (ex: TK_TYPE_RED_OUT)
            et space_before = 1
		current_char += 1 OU 2 (placer le curseur sur le char d'apres)


	else if current_char == doubleQuote
		int fin = get_index_of_next_doubleQuote(line, current_char ((+ 1)) )
		if (fin == -1)
			error: pas de quote fermante
			(On a pas a gerer)
			break ou return NULL ou ...
		creer un token avec le contenu entre les 2 doubleQuote (ft_substr) (sans les quotes !!!)
		token.type = TK_TYPE_STR
		token.escape_env_var = false (on remplacera les env_vars)
		placer le curseur sur le char d'apres la quote fermante



	else if current_char == simpleQuote
		... la meme chose
		token.escape_env_var = true (on NE remplacera PAS les env_vars)
		... la meme chose

        


	else
		(on est sur un mot:   echo, -n, $USER, ...)
		debut = i
        fin = chercher la fin du mot et creer un token entre ces 2 char(ft_substr)
			==> (tant que char existe && char n'est pas dans "&|><(whiteSpace)" )
		token.type = TK_TYPE_STR
		token.escape_env_var = false (on remplacera les env_vars)
		placer le curseur sur le char d'apres le mot
        
       if (is_white_space (i > 0 && line[debut-1]))    (si ya un espace avant debut) 
            token->space_before = 1
        else
            token->space_before = 0
































*/