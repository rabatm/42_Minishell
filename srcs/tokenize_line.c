/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 06:12:02 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 16:11:37 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_op_token_and_return_id(char *line, int i, t_token **tokens)
{
	int		type;
	char	*val;
	int		op_id;

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
		op_id += 1;
	}
	free(val);
	return (op_id);
}

int	make_quote_token_and_return_id(char *line, int i, t_token **tokens)
{
	int		closing_quote_id;
	char	*val;
	int		type;
	t_token	*tmp;
	char	quote_type;

	quote_type = line[i];
	tmp = NULL;
	closing_quote_id = get_id_of_closing_quote(line, i);
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
	free(val);
	return (closing_quote_id + 1);
}

int	make_str_token_and_return_id(char *line, int i, t_token **tokens)
{
	int		end_str_id;
	char	*val;
	int		type;
	int		space_before;

	if (i > 0 && ft_is_white_space(line[i - 1]))
		space_before = 1;
	else
		space_before = 0;
	end_str_id = get_end_str_id(line, i);
	val = ft_substr(line, i, end_str_id - i);
	type = TK_TYPE_STR;
	make_list_tokens(tokens, val, type, space_before);
	free(val);
	return (end_str_id);
}

t_token	**free_tokens_and_return_null(t_token **tokens)
{
	free_tokens(tokens);
	return (NULL);
}

t_token	**tokenize_line(char *line)
{
	t_token	**tokens;
	int		i;

	tokens = (t_token **)ft_calloc(1, sizeof(t_token *));
	if (!tokens)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (ft_is_white_space(line[i]))
			i++;
		else if (line[i] == '&' || line[i] == '|'
			|| line[i] == '>' || line[i] == '<')
			i = make_op_token_and_return_id(line, i, tokens);
		else if (line[i] == '"' || line[i] == '\'')
		{
			i = make_quote_token_and_return_id(line, i, tokens);
			if (i == -1)
				return (free_tokens_and_return_null(tokens));
		}
		else
			i = make_str_token_and_return_id(line, i, tokens);
	}
	return (tokens);
}
