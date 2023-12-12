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

int	ft_is_builltins_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	return (0);
}

int ft_exec_builtins(t_data *data, char **argv)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		ft_echo(ft_tab_size(argv), argv, data->env);
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		builtin_cd(ft_tab_size(argv), argv, data->env);
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		builtin_pwd(ft_tab_size(argv), argv, data->env);
	if (ft_strncmp(argv[0], "export", 7) == 0)
		exec_export(ft_tab_size(argv), argv, data);
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		exec_unset(ft_tab_size(argv), argv, data);
	if (ft_strncmp(argv[0], "env", 4) == 0)
		// a ajouter par charles
	return (0);
}

int	ft_exec(t_data *data)
{
	char **argv;

	argv = get_cmd_array(data->tokens);
	if(!argv[0])
		return (1);
	if (ft_is_builltins_cmd(argv[0]))
		ft_exec_builtins(data, argv);
	else
		ft_exec_ext_command(argv, data->env);
	(void) argv;
	return (0);
}

int	ft_exec_ext_command(char **argv, char **env)
{
	char	**path;
	char	*cmd;
	int		ret;
	pid_t   pid;

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