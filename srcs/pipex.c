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
	printf("ICI\n");
	print_tokens(data->tokens);
	token_arrays = create_token_arrays(data->tokens, nbcmd);
	
	while (i < nbcmd)
	{
		//free(data->tokens);
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

	i = 0;
	nbcmd = 0;
	ft_count_pipe(data->tokens, &nbcmd);
	if (nbcmd == 1 )
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
	ft_wait_end(nbcmd, i, data);
	free(pipefd);
	}
	return (0);
}
