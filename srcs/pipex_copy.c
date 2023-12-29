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
/*
int	ft_exec_pipe(t_data *data)
{
	int nbcmd;
	int i;
	int j;

	t_token **token_arrays;
	char **argv;

	ft_count_pipe(data->tokens, &nbcmd);
	int pipefd[2*nbcmd];
	j = 0;
	while (j < nbcmd - 1)
	{
    	if (pipe(pipefd + j*2) < 0) {
        	perror("pipe");
        	exit(EXIT_FAILURE);
    	}
    	j++;
	}
	token_arrays = create_token_arrays(data->tokens, nbcmd);
	i = 0;
	while (i < nbcmd - 1 && nbcmd > 1)
	{
		pipe(pipefd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		argv = get_cmd_array(&token_arrays[i]);

		if(!argv[0])
			return (1);
		ft_exec_ext_command(argv, data);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
	}
	argv = get_cmd_array(&token_arrays[i]);
	ft_exec_ext_command(argv, data);
	return (0);
}
*/
int	ft_exec_pipe(t_data *data)
{
	int nbcmd;
	int i;
	int j;
	t_token **token_arrays;

	ft_count_pipe(data->tokens, &nbcmd);
	int pipefd[2 * (nbcmd - 1)];
	token_arrays = create_token_arrays(data->tokens, nbcmd);

	// Création des pipes
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
		if (pid == 0) { // Processus enfant
			// Redirection de stdout si ce n'est pas la dernière commande
			if (i < nbcmd - 1) {
				dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
			}
			// Redirection de stdin si ce n'est pas la première commande
			if (i > 0) {
				dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
			}

			// Fermer tous les descripteurs de fichier
			j = 0;
			while (j < 2 * (nbcmd - 1)) {
				close(pipefd[j]);
				j++;
			}

			// Exécution de la commande
			ft_exec(data); 
			exit(EXIT_FAILURE);
		} else if (pid < 0) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		i++;
	}

	// Fermer tous les descripteurs de fichier dans le processus parent
	j = 0;
	while (j < 2 * (nbcmd - 1)) {
		close(pipefd[j]);
		j++;
	}

	// Attendre tous les processus enfants
	i = 0;
	while (i < nbcmd) {
		wait(NULL);
		i++;
	}

	return (0);
}

