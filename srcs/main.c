/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/12 17:59:51 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//****************a supprimer
 void   print_tokens(t_token **tokens)
 {
    t_token *tmp;
    if (tokens)
    {
        tmp = *tokens;
        printf("------------------------------\n");
        while (tmp)
        {
            printf("Valeur : %10s \t Type : %10d   \t   escape_env_var= %5d \n", tmp->val, tmp->type, tmp->escape_env_var);
            tmp = tmp->next;
        }
        printf("------------------------------\n");
    }
}
/*
void    ft_print_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}
*/

void    free_and_exit_if_forbidden_token(t_data *data)
{
    t_token *tmp;

    tmp = *data->tokens;
    while (tmp)
    {
        if (tmp->type == TK_TYPE_AND || tmp->type == TK_TYPE_OR)
        {
            printf("sorry, dont write %s we didn't do the bonus\n", tmp->val);
            free_data(data);
            exit(0);
        }
        tmp=tmp->next;
    }
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = init_data(env);
	//handle_signal();	// * Handle ctrl+C and ctrl+D
	while (1)
	{
		//handle_signal();
		data->line = readline("Myshell $>");
		if (!data->line)
		{
		data->exit = 1;
		data->line = ft_strdup("");
		}
        else
        {
            add_history(data->line);
        	data->tokens = tokenize_line(data->line);
            free_and_exit_if_forbidden_token(data);
            //debug
            //print_tokens (data->tokens);
            replace_env_var(data);
           // print_tokens (data->tokens);
            ft_exec(data);
            free_tokens(data->tokens);
        }
	}
	return (0);
}
