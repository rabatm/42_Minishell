/*#include "../includes/minishell.h"

void ft_count_pipe(t_token **tokens, int *count)
{
	t_token	*tmp;

	*count = 1;
	tmp = *tokens;
	while(tmp)
	{
		if (tmp->type == TK_TYPE_PIPE)
			*count = *count + 1;
		tmp = tmp->next;
	}
}

int	ft_exec_pipe(t_data *data)
{
	int nbcmd;
	int i;
	int pipefd[2];
	pid_t *pids;
	t_token **token_arrays;
	char **argv;

	ft_count_pipe(data->tokens, &nbcmd);
	if (nbcmd == 1)
		ft_exec(data);
	else {
	token_arrays = create_token_arrays(data->tokens, nbcmd);
	}
	pids = malloc(sizeof(pid_t) * nbcmd);
	i = 0;
	while (i < nbcmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i < nbcmd - 1)
			{
				dup2(pipefd[i + 1], STDOUT_FILENO);
				dup2(pipefd[i + 1], STDIN_FILENO);
				close(pipefd[i]);
			}
			if (i == 0)
			{
				dup2(pipefd[i + 1], STDOUT_FILENO);
				close(pipefd[i]);
			}
			if (i == (nbcmd - 1))
			{
				close(pipefd[i]);
			}
			argv = get_cmd_array(&token_arrays[i]);
			if(!argv[0])
				return (1);
			if (ft_is_builltins_cmd(argv[0]))
				ft_exec_builtins(data, argv);
			else
			ft_exec_ext_command(argv, data);
				exit(0);
		}
		else if (pids[i] < 0)
		{
			printf("Error\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < nbcmd - 1)
	{
		close(pipefd[i * 2]);
		close(pipefd[i * 2 + 1]);
		i++;
	}
	i = 0;
	while (i < nbcmd)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pipefd);
	free(pids);
	return (0);
}
*/
