/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:16:55 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 15:37:41 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_env_var(t_data *data, int var_id)
{
	int		i;

	free(data->env[var_id]);
	i = var_id;
	while (data->env[i])
	{
		data->env[i] = data->env[i + 1];
		i++;
	}
}

int	get_env_var_id(char *var_name, char **env)
{
	int		i;
	char	*equal_sign;
	size_t	len;

	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
			len = equal_sign - env[i];
		else
			len = ft_strlen(env[i]);
		if (ft_strncmp(env[i], var_name, len) == 0
			&& ft_strlen(var_name) == len)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_unset(int argc, char **argv, t_data *data)
{
	int		arg_id;
	int		var_id;

	arg_id = 1;
	while (arg_id < argc)
	{
		var_id = get_env_var_id(argv[arg_id], data->env);
		if (var_id != -1)
			remove_env_var(data, var_id);
		arg_id++;
	}
	return (0);
}
