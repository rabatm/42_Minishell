/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:47:26 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/12 17:02:05 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_value_of_env_var(t_data *data, char *env_var)
{
    int     i;
    int    len;

    if (!env_var || !data)
        return (NULL);
    i = 0;
    len = ft_strlen(env_var);
    while (data->env[i])
    {
        if (ft_str_starts_with(data->env[i], env_var) && data->env[i][len] == '=')
            return (ft_strdup(data->env[i] + len + 1));
        i++;
    }
    return (NULL);
}



void    replace_env_var(t_data *data)
{
    t_token *tmp;
    int     i;
    int     j;
    char    *tmp_val;
    char    *tmp_env_var;
    char    *new_val;

    tmp = *data->tokens;
    while (tmp)
    {
        if (tmp->type == TK_TYPE_STR && tmp->escape_env_var == 0)
        {
            i = 0;
            while (tmp->val[i])
            {
                if (tmp->val[i] == '$')
                {
                    j = i + 1;
                    if (tmp->val[j] == '?')
                    {
                        tmp->val = ft_itoa(data->last_exit_status);
                    }
                    else
                    {
                        while (tmp->val[j] && !ft_is_white_space(tmp->val[j]) && tmp->val[j] != '$')
                            j++;
                        tmp_env_var = ft_substr(tmp->val, i + 1, j - i - 1);
                        tmp_val = get_value_of_env_var(data, tmp_env_var);
                        free(tmp_env_var);
                        tmp_env_var = NULL;
                        if (tmp_val)
                        {
                            new_val = ft_str_replace(tmp->val, tmp_val, i, i + j);
                            free(tmp_val);
                            free(tmp->val);
                            tmp->val = new_val;
                            i += ft_strlen(tmp_val) - 1;

                        }
                    }
                }
                i++;
            }
        }
        tmp = tmp->next;
    }
}
