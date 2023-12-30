/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:43:08 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 20:43:12 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_token_array(t_token **token_array)
{
	t_token	*tmp;
	int		i;

	i = 0;
	while (token_array[i])
	{
		printf("Pointer _array[%d] = %p\n", i, token_array[i]);
		tmp = token_array[i];
		while (tmp)
		{
			printf("liste du p token_array %s \n", tmp->val);
			tmp = tmp->next;
		}
		i++;
	}
}

t_token	**create_token_arrays(t_token **tokens, int nbpipes)
{
	t_token	*current_token;
	t_token	**token_arrays;
	t_token	*tmp;
	int		i;

	current_token = *tokens;
	i = 0;
	token_arrays = malloc(sizeof(t_token *) * (nbpipes + 1));
	while (current_token)
	{
		token_arrays[i] = current_token;
		while (current_token && current_token->type != TK_TYPE_PIPE)
			current_token = current_token->next;
		i++;
		if (current_token && current_token->next)
		{
			tmp = current_token->next;
			current_token->previous->next = NULL;
			free(current_token);
			current_token = tmp;
		}
	}
	token_arrays[i] = NULL;
	return (token_arrays);
}

void	ft_fork_and_exec(t_data *data, int *pipefd, int i, int nbcmd)
{
	pid_t	pid;
	int		j;

	j = 0;
	pid = fork();
	if (pid == 0)
	{
		if (i < nbcmd - 1)
			dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
		if (i > 0)
			dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
		j = 0;
		while (j < 2 * (nbcmd - 1))
		{
			close(pipefd[j]);
			j++;
		}
		ft_exec(data);
		exit(data->last_exit_status);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
