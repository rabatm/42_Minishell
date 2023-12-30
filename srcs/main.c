/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 21:02:12 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	merge_tokens_if_no_space_before(t_token **tokens)
{	
	t_token	*tmp;
	char	*merged_val;
	t_token	*next_token;

	tmp = *tokens;
	tmp = tmp->next;
	while (tmp && tmp->next)
	{
		next_token = tmp->next;
		if (tmp->next->space_before == 0 && tmp->next->type == TK_TYPE_STR)
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

void	free_and_exit_if_forbidden_token(t_data *data)
{
	t_token	*tmp;

	tmp = *data->tokens;
	while (tmp)
	{
		if (tmp->type == TK_TYPE_AND || tmp->type == TK_TYPE_OR)
		{
			printf(RED "sorry, dont write [%s] we didn't do the bonus\n" RST, tmp->val);
			break ;
		}
		tmp=tmp->next;
	}
	if (tmp)
	{
		free_data(data);
		exit(0);
	}
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
		if (!data->line)
		{
			data->exit = 1;
			if (data->line)
			{
				free(data->line);
				data->line = NULL;
			}
			data->line = ft_strdup("");
		}
		else
		{
			add_history(data->line);
			data->tokens = tokenize_line(data->line);
			if (data->tokens && *data->tokens)
			{
				free_and_exit_if_forbidden_token(data);
				replace_env_var(data);
				merge_tokens_if_no_space_before(data->tokens);
				ft_exec_pipe(data);
				free_tokens(data->tokens);
				data->tokens = NULL;
			}
			else
				continue;
		}
		if (data->line)
		{
			free(data->line);
			data->line = NULL;
		}
		if (data->tokens)
		{
			free_tokens(data->tokens);
            data->tokens = NULL;
        }
        if (data->exit == 1)
        {
            free_data(data);
            data = NULL;
            break;
        }
    if (data)
    {
        free_data(data);
        data = NULL;
    }
	return (0);
}
