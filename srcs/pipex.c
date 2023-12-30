#include "../includes/minishell.h"

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
	int j;
	t_token **token_arrays;

	ft_count_pipe(data->tokens, &nbcmd);
	int pipefd[2 * (nbcmd - 1)];
	token_arrays = create_token_arrays(data->tokens, nbcmd);
	j = 0;
	while (j < nbcmd - 1) {
		if (pipe(pipefd + j * 2) < 0) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		j++;
	}

	i = 0;
	while (i < nbcmd) {
		data->tokens = &token_arrays[i];
		pid_t pid = fork();
		if (pid == 0) {
			if (i < nbcmd - 1) {
				dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
			}
			if (i > 0) {
				dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
			}
			j = 0;
			while (j < 2 * (nbcmd - 1)) {
				close(pipefd[j]);
				j++;
			}
			ft_exec(data);
			exit(EXIT_FAILURE);
		} else if (pid < 0) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	j = 0;
	while (j < 2 * (nbcmd - 1)) {
		close(pipefd[j]);
		j++;
	}
	i = 0;
	while (i < nbcmd) {
		wait(NULL);
		i++;
	}
	return (0);
}

