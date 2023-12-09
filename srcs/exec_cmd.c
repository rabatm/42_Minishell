#include "../includes/minishell.h"

char	**get_cmd_array(t_token **tokens)
{
	int		tk_size;
	t_token	*tmp;
	char	**argv;
	int		i;

	i = 0;
	tk_size = ft_tokensize(tokens);
	tmp = *tokens;
	argv = malloc(sizeof(char *) * (tk_size +1));
	if (!argv)
		return (NULL);
	while(tmp)
	{
		argv[i] = tmp->val;
		i ++;
		tmp = tmp->next;
	}
	return (argv);
}

int	ft_exec(t_data *data)
{
	char **argv;

	argv = get_cmd_array(data->tokens);
	ft_exec_ext_command(1, argv, data->env);
	(void) argv;
	return (0);
}

int	ft_is_builltins_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	return (0);
}

int	ft_exec_ext_command(int argc, char **argv, char **env)
{
	char	**path;
	char	*cmd;
	int		ret;
	pid_t   pid;

	(void) argc;
	path = ft_getenvpath(env);
	cmd = ft_checkexe(argv[0], path);
	if (cmd == NULL)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		ret = execve(cmd, argv, env);
		exit(ret);
	}
	else
	{
		wait(NULL);
	}
	return(0);
}