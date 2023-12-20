/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:47:26 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/19 17:43:33 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
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
        if (ft_strncmp(data->env[i], env_var, len) == 0 && data->env[i][len] == '=')
            return (ft_strdup(data->env[i] + len + 1));
        i++;
    }
    return (NULL);
}
*/

char    *ft_str_replace(char *str, char *new_val, int start, int end)
{
    char    *new_str;
    int     i;
    int     j;
    int     k;
    int     len_str;

    len_str = ft_strlen(str) - (end - start);
    if (!str || !new_val)
        return (NULL);
    new_str = (char *)ft_calloc(len_str + ft_strlen(new_val) + 1, sizeof(char));
    if (!new_str)
        return (NULL);
    i = 0;
    while (i < start)
    {
        new_str[i] = str[i];
        i++;
    }
    j = 0;
    while (new_val[j])
    {
        new_str[i] = new_val[j];
        i++;
        j++;
    }
    k = end;
    while (str[k])
    {
        new_str[i] = str[k];
        i++;
        k++;
    }
    return (new_str);
}

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
        if (ft_strncmp(data->env[i], env_var, len) == 0 && data->env[i][len] == '=')
            return (ft_strdup(data->env[i] + len + 1));
        i++;
    }
    return (NULL);
}

char    *replace_env_var_by_value(t_data *data, char *str)
{
    int     i;
    int     j;
    char    *tmp_val;
    char    *tmp_env_var;
    char    *new_val;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            j = i + 1;
            if (str[j] == '?')
            {
                tmp_val = ft_itoa(data->last_exit_status);
                j++;
            }
            else
            {
                while (isalnum(str[j]) || str[j] == '_' || isalpha(str[j]))
                //while (str[j] && !ft_is_white_space(str[j]) && str[j] != '$' )
                    j++;
                tmp_env_var = ft_substr(str, i + 1, j - i - 1);
                tmp_val = get_value_of_env_var(data, tmp_env_var);
                free(tmp_env_var);
                tmp_env_var = NULL;
            }
            if (tmp_val)
            {
                new_val = ft_str_replace(str, tmp_val, i, i + j);
                free(tmp_val);
                free(str);
                str = new_val;
                i += ft_strlen(tmp_val) - 1;
            }
        }
        i++;
    }
    return (str);
}


void    replace_env_var(t_data *data)
{
    t_token *tmp;

    tmp = *data->tokens;
    while (tmp)
    {
        if (tmp->type == TK_TYPE_STR && tmp->escape_env_var == 0)
            tmp->val = replace_env_var_by_value(data, tmp->val);
        tmp = tmp->next;
    }
}

/*
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
                        while (tmp->val[j] && !ft_is_white_space(tmp->val[j]) && tmp->val[j] != '$' )
                        //while (isalpha(tmp->val[j]) || isalnum(tmp->val[j]) || tmp->val[j] == '_')
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
*/
/*
                        real        ms
echo "$USER'"          sv'        $USER'     // ERROR
echo "$USERE"          svE        $USERE     // ERROR
echo "'$USER"           'sv         'sv         // OK







*/
