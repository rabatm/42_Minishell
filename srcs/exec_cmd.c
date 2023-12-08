#include "../includes/minishell.h"

char	*get_cmd_array(t_token **tokens)
{
	int		tk_size;
	t_token	*tmp;
	char	*argv;
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

int	ft_exec(int argc, char **argv, t_data *data)
{
	char *argv;

	argv = get_cmd_array(data->tokens);
}
int	ft_exec_ext_command(int argc, char **argv, char **env)
{
	char	*path;
	char	*cmd;
	int		ret;

	(void) argc;
	path = ft_getenvpath(env);
	cmd = ft_checkexe(argv[0], &path);
	if (cmd == NULL)
		return (1);
	ret = execve(cmd, argv, env);
	return(ret);
}