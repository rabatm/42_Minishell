#include "../includes/minishell.h"

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

char **ft_make_data_for_exec(t_data *data)
{
	char	**data_for_pipe;
	char	*line;

	line = data->line;
	data_for_pipe = ft_split(line, '|');
	return(data_for_pipe);
}
int	ft_count_pipe(t_token **tokens)
{
	int	count;
	t_token	*tmp;

	count = 0;
	tmp = *tokens;
	while(tmp)
	{
		if (tmp->type == TK_TYPE_PIPE)
			count++;
		tmp = tmp->next;
	}
		fprintf(stderr, "coutnpip\n");
	return (count);
}

void	ft_exec_pipe(t_data *data)
{
	int nbpipes;
	//int i;
	//int *pipefd;
	//pid_t *pids;
	char **data_for_pipe;
	nbpipes = ft_count_pipe(data->tokens);
	if (nbpipes == 0)
		return ;
	
	data_for_pipe = ft_make_data_for_exec(data);
	printf("data_for_pipe[0] = %s\n", data_for_pipe[0]);
	printf("data_for_pipe[1] = %s\n", data_for_pipe[1]);

	printf("nbpipes = %d\n", nbpipes);
	/*
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
	*/
	
}

