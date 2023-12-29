#include "../includes/minishell.h"

void ft_count_pipe(t_token **tokens, int *count)
{
	t_token	*tmp;

	*count = 0;
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
	int *pipefd;
	pid_t *pids;
	t_token ***token_arrays;
	char **argv;

	ft_count_pipe(data->tokens, &nbcmd);
	if (nbcmd == 0)
		return -1;	  
	token_arrays = create_token_arrays(*data->tokens, nbcmd);
	pipefd = (int *)malloc(sizeof(int) * (nbcmd + 1));
	if (!pipefd)
		return -1;
	pids = malloc(sizeof(pid_t) * nbcmd);
  	if (pids == NULL) {
		perror("Erreur lors de l'allocation de la mémoire");
		return -1;
  	}
	i = 0;
	while (i < nbcmd) {
		if (pipe(pipefd + i) == -1) {
			perror("Erreur lors de la création du tube");
			return -1;
		}
		i++;
	}
	i = 0;
	while (i < nbcmd) {
	pids[i] = fork();
	if (pids[i] == -1) {
		perror("Erreur lors de la création du processus");
		return -1;
	}
	if (pids[i] == 0) {
		// Processus i

		// Ferme les extrémités des tubes qui ne sont pas utilisées
		int j = 0;
		while (j < nbcmd) {
		if (i != j) {
          close(pipefd[i * (nbcmd - 1) + j]);
          close(pipefd[j * (nbcmd - 1) + i]);
        }
        j++;
      }

      // Redirige l'entrée et la sortie vers les tubes appropriés
      if (i == 0) {
        // Premier processus
        dup2(pipefd[i], STDIN_FILENO);
      } else if (i == nbcmd) {
        // Dernier processus
        dup2(pipefd[i - 1], STDOUT_FILENO);
      } else {
        // Processus intermédiaire
        dup2(pipefd[i - 1], STDIN_FILENO);
        dup2(pipefd[i], STDOUT_FILENO);
      }
		argv = get_cmd_array(token_arrays[i]);
			if(!argv[0])
		return (1);
	if (ft_is_builltins_cmd(argv[0]))
		ft_exec_builtins(data, argv);
	else
		ft_exec_ext_command(argv, data);
		// Exécute la commande i
	  //fprintf(stderr, "data_for_pipe[i] = %s\n", token_arrays[i][0]);
	  //ft_exec_ext_command(&token_arrays[i], data);
    }
    i++;
  }

  // Attend la fin des processus
  i = 0;
  while (i < nbcmd) {
    waitpid(pids[i], NULL, 0);
    i++;
  }

  // Libère la mémoire
  free(pipefd);
  free(pids);

  return 0;
}

