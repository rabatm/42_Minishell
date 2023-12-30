/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarie <mmarie@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:58:11 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 17:07:30 by mmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// data->heredoc_handled = 0;
int	apply_redirection_in(t_data *data, t_token *token)
{
	int	fd;

	if (data->heredoc_handled == 0 && ft_rediretion_error(data, token))
		return (1);
	if (data->heredoc_handled == 1)
		fd = open (".heredoc", O_RDONLY);
	else
		fd = open(token->next->val, O_RDONLY);
	if (fd == -1)
		return (handle_error_fd(data, token, fd));
	if (data->original_stdin == -1)
		data->original_stdin = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (handle_error_fd(data, token, fd));
	data->current_stdin = fd;
	close(fd);
	return (0);
}

int	apply_redirection_out_append(t_data *data, t_token *token)
{
	int	fd;

	if (ft_rediretion_error(data, token))
		return (1);
	fd = open(token->next->val, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (handle_error_fd(data, token, fd));
	if (data->original_stdout == -1)
		data->original_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (handle_error_fd(data, token, fd));
	data->current_stdout = fd;
	close(fd);
	return (0);
}

int	apply_redirection_out(t_data *data, t_token *token)
{
	int	fd;

	if (ft_rediretion_error(data, token))
		return (1);
	fd = open(token->next->val, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (handle_error_fd(data, token, fd));
	if (data->original_stdout == -1)
		data->original_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (handle_error_fd(data, token, fd));
	data->current_stdout = fd;
	close(fd);
	return (0);
}

int	dothispls(t_token *tmp, t_data *data)
{
	if (data->current_stdout != STDOUT_FILENO && data->current_stdout != -1)
		close(data->current_stdout);
	return (apply_redirection_out_append(data, tmp));
}

int	apply_redirections(t_data *data, t_token **tokens)
{
	t_token	*tmp;
	int		ret;

	ret = 0;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == TK_TYPE_RED_OUT)
			ret = apply_redirection_out(data, tmp);
		else if (tmp->type == TK_TYPE_RED_OUT_APPEND)
			ret = dothispls(tmp, data);
		if (ret == 1)
			return (ret);
		if (tmp->type == TK_TYPE_RED_IN)
			ret = apply_redirection_in(data, tmp);
		if (tmp->type == TK_TYPE_RED_IN_DELIM)
		{
			ret = apply_redirection_in_delim(data, tmp);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (ret);
}
