/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 21:03:40 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 21:03:56 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_and_or_type(char *line, int i)
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

int	get_redirection_type(char *line, int i)
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

int	get_token_type(char *line, int i)
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

int	get_id_of_closing_quote(char *line, int opening_quote_id)
{
	char	quote_type;

	quote_type = line[opening_quote_id];
	opening_quote_id ++;
	while (line[opening_quote_id])
	{
		if (line[opening_quote_id] == quote_type)
			return (opening_quote_id);
		opening_quote_id++;
	}
	return (-1);
}

int	get_end_str_id(char *line, int start_str_id)
{
	start_str_id ++;
	while (line[start_str_id]
		&& !ft_is_white_space(line[start_str_id])
		&& line[start_str_id] != '&'
		&& line[start_str_id] != '|'
		&& line[start_str_id] != '>'
		&& line[start_str_id] != '<'
		&& line[start_str_id] != '"'
		&& line[start_str_id] != '\'')
		start_str_id++;
	return (start_str_id);
}
