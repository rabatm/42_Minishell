/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:37:24 by mmarie            #+#    #+#             */
/*   Updated: 2023/12/31 00:47:49 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

void	ft_exec_builtins(t_data *data, char **argv)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		ret = ft_echo(ft_tab_size(argv), argv, data->env);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		ret = builtin_cd(ft_tab_size(argv), argv, data->env);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		ret = builtin_pwd(ft_tab_size(argv), argv, data->env);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		ret = exec_export(ft_tab_size(argv), argv, data);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		ret = exec_unset(ft_tab_size(argv), argv, data);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		ret = exec_env(data);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		ret = ft_exit(data);
	data->last_exit_status = ret;
}

void	exec_external_command(char *cmd, char **argv, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(cmd, argv, data->env);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->last_exit_status = WEXITSTATUS(status);
		else
			data->last_exit_status = 128 + WTERMSIG(status);
	}
}

void	ft_exec_ext_command(char **argv, t_data *data)
{
	char	**path;
	char	*cmd;

	path = ft_getenvpath(data->env);
	cmd = ft_checkexe(argv[0], path);
	if (cmd == NULL)
		data->last_exit_status = 1;
	else
		exec_external_command(cmd, argv, data);
	ft_free_tab(path);
	free(cmd);
}

int	ft_exec(t_data *data)
{
	char	**argv;

	if (apply_redirections(data, data->tokens) == 1)
	{
		reset_redirections(data);
		return (1);
	}
	if (data->heredoc_handled == 1)
	{
		apply_redirection_in(data, *data->tokens);
	}
	argv = get_cmd_array(data->tokens);
	if (!argv[0])
		return (1);
	if (ft_is_builltins_cmd(argv[0]))
		ft_exec_builtins(data, argv);
	else
		ft_exec_ext_command(argv, data);
	reset_redirections(data);
	free_tokens(data->tokens);
	free(argv);
	return (0);
}
