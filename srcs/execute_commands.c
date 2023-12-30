/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:04:09 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/29 13:28:00 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_argv(t_token **tokens, char **argv)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == TK_TYPE_RED_IN || tmp->type == TK_TYPE_RED_OUT
		|| tmp->type == TK_TYPE_RED_OUT_APPEND
		|| tmp->type == TK_TYPE_RED_IN_DELIM)
		{
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
			else
				break ;
		}
		else if (tmp->type == TK_TYPE_STR)
		{
			argv[i] = tmp->val;
			i ++;
			tmp = tmp->next;
		}
	}
	argv[i] = NULL;
}

char	**get_cmd_array(t_token **tokens)
{
	int		tk_size;
	char	**argv;

	tk_size = ft_tokensize(tokens);
	argv = (char **)ft_calloc(tk_size + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	fill_argv(tokens, argv);
	return (argv);
}

/*
char	**get_cmd_array(t_token **tokens)
{
	int		tk_size;
	t_token	*tmp;
	char	**argv;
	int		i;

	i = 0;
	tk_size = ft_tokensize(tokens);
	tmp = *tokens;
	argv = (char **)ft_calloc(tk_size + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	while(tmp)
	{
		if (tmp->type == TK_TYPE_RED_IN || tmp->type == TK_TYPE_RED_OUT
		|| tmp->type == TK_TYPE_RED_OUT_APPEND || tmp->type == TK_TYPE_RED_IN_DELIM)
		{
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
			else
				break ;
		}
		else if (tmp->type == TK_TYPE_STR)
		{
			argv[i] = tmp->val;
			i ++;
			tmp = tmp->next;
		}
	}
	argv[i] = NULL;
	return (argv);
}
*/
