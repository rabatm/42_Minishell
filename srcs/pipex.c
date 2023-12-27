#include "./includes/minishell.h"

t_token *news_token_for_pipe(t_token *token)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = token->type;
	new->val = ft_strdup(token->val);
	new->next = NULL;
	return (new);
}

t_data **ft_make_data_for_exec(t_data **data, int nbpipes)
{
	t_data **data_for_pipe;

	data_for_pipe = (t_data **)malloc(sizeof(t_data *) * (nbpipes + 1));
	if (!data_for_pipe)
		return (NULL);
	data_for_pipe[nbpipes] = NULL;
	data_for_pipe = ft_split(data, TK_TYPE_PIPE);
	return(data_for_pipe);
}
int	ft_count_pipe(t_data *data)
{
	int		i;
	int		count;
	t_token	*tmp;

	i = 0;
	count = 0;
	tmp = data->tokens;
	while(tmp)
	{
		if (tmp->type == TK_TYPE_PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	ft_exec_pipe(t_pipex *data)
{
	int nbpipes;
	int i;
	int *pipefd;
	pid_t *pids;
	t_data **data_for_pipe;

	nbpipes = ft_count_pipe(data);
	if (nbpipes == 0)
		return ;
	
	data_for_pipe = ft_make_data_for_exec(data, nbpipes);
	pipefd = (int *)malloc(sizeof(int) * (nbpipes * 2));
	if (!pipefd)
		return ;
	i = 0;
	while(i < nbpipes - 1)
	{
		if (pipe(pipefd + 1) == -1)
			return ;
		i++;
	}
	i = 0;
	while (nbpipes > i)
	{
	}
	
}

