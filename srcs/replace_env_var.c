/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:47:26 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/28 17:08:41 by svanmarc         ###   ########.fr       */
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
        if (ft_strncmp(data->env[i], env_var, len) == 0 && data->env[i][len] == '=')
            return (ft_strdup(data->env[i] + len + 1));
        i++;
    }
    return (NULL);
}

/*
0123456789
   i    j
ac-$USER-ddddddddddd

svanmarc     replace


i =3
j =8


new_str = str[0] a str[i-1]           +             replace         +   str[j+1] a str[len(str) - 1]




*/
char    *replace_env_var_by_value(t_data *data, char *str)
{
    int     i;
    int     j;
    char    *tmp_val;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] != '\0' && !ft_is_white_space(str[i + 1]))
        {
            if (str[i + 1] == '?')
            {
                tmp_val = ft_itoa(data->last_exit_status);
                str = ft_str_replace_version_3(str, tmp_val, i, i + 2);
                if (!str)
                {
                    free(tmp_val);
                    return (NULL);
                }
                if (tmp_val)
                {
                    i += ft_strlen(tmp_val) - 1;
                    free(tmp_val);
                }
                else
                    i += 1;
            }
            else
            {
                j = i + 1;
                while (str[j] != '\0' && (isalnum(str[j]) || str[j] == '_'))
                    j++;
                tmp_val = get_value_of_env_var(data, ft_substr(str, i + 1, j - i - 1));
                str = ft_str_replace_version_3(str, tmp_val, i, j);
                if (!str)
                {
                    free(tmp_val);
                    return (NULL);
                }
                if (tmp_val)
                {
                    i += ft_strlen(tmp_val) - 1;
                    free(tmp_val);
                }
                else
                    i += j - i - 1;
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
        if (tmp->type == TK_TYPE_STR && tmp->change_env_var == 0)
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
