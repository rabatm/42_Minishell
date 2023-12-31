/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/31 01:15:03 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	merge_tokens_if_no_space_before(t_token **tokens)
{
	t_token		*tmp;
	char		*merged_val;
	t_token		*next_token;

	tmp = *tokens;
	tmp = tmp->next;
	while (tmp && tmp->next)
	{
		next_token = tmp->next;
		if (tmp->next->space_before == 0
			&& tmp->next->type == TK_TYPE_STR && tmp->type == TK_TYPE_STR)
		{
			merged_val = ft_strjoin(tmp->val, next_token->val);
			free(tmp->val);
			free(next_token->val);
			tmp->val = merged_val;
			next_token = tmp->next;
			tmp->next = next_token->next;
			if (tmp->next)
				tmp->next->previous = tmp;
			free(next_token);
		}
		else
			tmp = tmp->next;
	}
}

int	free_and_exit_if_forbidden_token(t_data *data)
{
	t_token	*tmp;

	tmp = *data->tokens;
	while (tmp)
	{
		if (tmp->type == TK_TYPE_AND || tmp->type == TK_TYPE_OR)
		{
			printf(RED "sorry, dont write [%s]", tmp->val);
			printf(RED "we didn't do the bonus\n" RST);
			return (1);
		}
		tmp = tmp->next;
	}
	if (tmp)
		free_data(data);
	return (0);
}

void	ft_ftok(t_token **tokens)
{
	if (tokens)
	{
		free_tokens(tokens);
		tokens = NULL;
	}
}

int	ft_minishell(t_data *data)
{
	if (!data->line)
	{
		data->exit = 1;
		data->line = ft_strdup("");
	}
	else
	{
		add_history(data->line);
		data->tokens = tokenize_line(data->line);
		if (data->tokens && *data->tokens)
		{
			if (free_and_exit_if_forbidden_token(data) == 1)
				return (1);
			replace_env_var(data);
			merge_tokens_if_no_space_before(data->tokens);
			ft_exec_pipe(data);
			ft_ftok(data->tokens);
		}
		else
		{
			ft_ftok(data->tokens);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = init_data(env);
	handle_signal();
	while (1)
	{
		data->line = readline("Myshell $>");
		if (ft_minishell(data))
			continue ;
		if (data->line)
		{
			free(data->line);
			data->line = NULL;
		}
		ft_ftok(data->tokens);
		if (data->exit == 1)
			break ;
	}
	free_data(data);
	return (0);
}
