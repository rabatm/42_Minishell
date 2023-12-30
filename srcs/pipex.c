/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:00:19 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 20:02:26 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_count_pipe(t_token **tokens, int *count)
{
	t_token	*tmp;

	*count = 1;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == TK_TYPE_PIPE)
			*count = *count + 1;
		tmp = tmp->next;
	}
}

void	ft_launch_cmd(int nbcmd, t_data *data, int *pipefd)
{
	int		i;
	t_token	**token_arrays;

	i = 0;
	token_arrays = create_token_arrays(data->tokens, nbcmd);
	while (i < nbcmd)
	{
		data->tokens = &token_arrays[i];
		ft_fork_and_exec(data, pipefd, i, nbcmd);
		i++;
	}
}

int	*ft_make_pipefd(int nbcmd)
{
	int	i;
	int	*pipefd;

	pipefd = malloc(sizeof(int) * 2 * (nbcmd - 1));
	i = 0;
	while (i < nbcmd - 1)
	{
		if (pipe(pipefd + i * 2) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipefd);
}

int	ft_exec_pipe(t_data *data)
{
	int	nbcmd;
	int	i;
	int	*pipefd;
	int	status;

	ft_count_pipe(data->tokens, &nbcmd);
	if (nbcmd == 1)
		ft_exec(data);
	else
	{
		pipefd = ft_make_pipefd(nbcmd);
		i = 0;
		ft_launch_cmd(nbcmd, data, pipefd);
		while (i < 2 * (nbcmd - 1))
		{
			close(pipefd[i]);
			i++;
		}
		i = 0;
		while (i < nbcmd)
		{
			wait(&status);
			i++;
		}
		if (WIFEXITED(status))
			data->last_exit_status = WEXITSTATUS(status);
		else
			data->last_exit_status = 128 + WTERMSIG(status);
	}
	return (0);
}
