/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:47:26 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 22:24:12 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value_of_env_var(t_data *data, char *env_var)
{
	int	i;
	int	len;

	if (!env_var || !data)
		return (NULL);
	i = 0;
	len = ft_strlen(env_var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], env_var, len) == 0
			&& data->env[i][len] == '=')
			return (ft_strdup(data->env[i] + len + 1));
		i++;
	}
	return (NULL);
}

int	replace_exit_status_and_get_idx(char **str_ptr, int i, t_data *data)
{
	char	*tmp_val;

	tmp_val = ft_itoa(data->last_exit_status);
	*str_ptr = ft_str_replace_version_3(*str_ptr, tmp_val, i, i + 2);
	if (!*str_ptr)
	{
		free(tmp_val);
		return (i);
	}
	if (tmp_val)
	{
		i += ft_strlen(tmp_val) - 1;
		free(tmp_val);
	}
	else
		i += 1;
	return (i);
}

int	replace_var_and_get_idx(char **str_ptr, int i, t_data *data, int *j_ptr)
{
	char	*tmp_val;
	char	*tmp_env_var;
	char	*new_val;

	while ((*str_ptr)[*j_ptr] != '\0'
		&& (isalnum((*str_ptr)[*j_ptr]) || (*str_ptr)[*j_ptr] == '_'))
		(*j_ptr)++;
	tmp_env_var = ft_substr(*str_ptr, i + 1, *j_ptr - i - 1);
	tmp_val = get_value_of_env_var(data, tmp_env_var);
	free(tmp_env_var);
	tmp_env_var = NULL;
	if (tmp_val)
	{
		new_val = ft_str_replace_version_3(*str_ptr, tmp_val, i, *j_ptr);
		free(tmp_val);
		free(*str_ptr);
		*str_ptr = new_val;
		i += ft_strlen(tmp_val) - 1;
	}
	else
		i += *j_ptr - i - 1;
	return (i);
}

char	*replace_env_var_by_value(t_data *data, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0'
			&& !ft_is_white_space(str[i + 1]))
		{
			if (str[i + 1] == '?')
				i = replace_exit_status_and_get_idx(&str, i, data);
			else
			{
				j = i + 1;
				i = replace_var_and_get_idx(&str, i, data, &j);
			}
		}
		i++;
	}
	return (str);
}

void	replace_env_var(t_data *data)
{
	t_token	*tmp;

	tmp = *data->tokens;
	while (tmp)
	{
		if (tmp->type == TK_TYPE_STR && tmp->change_env_var == 0)
			tmp->val = replace_env_var_by_value(data, tmp->val);
		tmp = tmp->next;
	}
}

