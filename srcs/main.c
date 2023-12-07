/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/07 18:21:48 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    debug_create_fake_history(void)
{
    add_history("env | sort");
    add_history("echo ABC > _out || echo $?");
	add_history("export CC=ccccccccccc");
	add_history("export BB=bbbbbbbbbbbbbbb");
	add_history("export AA =aaaaaaaaaa");
    add_history("abc 'ABC' def");
    add_history("echo $USER");
    add_history("echo $USER > output.txt | cat < input.txt ; echo Fini");
    add_history(", ,, . .. | & ; ;; ( ) < << > >> $");
    add_history("""q"" ""x""");
    add_history("echo   '   $USER  '   > output.txt | cat < input.txt ; echo Fini");
}


//****************a supprimer
 void   ft_print_tokens(t_token **tokens)
 {
    t_token *tmp;
    if (tokens)
    {
        // * DEBUG
        tmp = *tokens;
        printf("------------------------------\n");
        while (tmp)
        {
            printf("Valeur : %10s \t Type : %10d   \t   escape_env_var= %5d \n", tmp->val, tmp->type, tmp->escape_env_var);
            tmp = tmp->next;
        }
        printf("------------------------------\n");
        // * DEBUG
    }
}


void    ft_free_and_exit_if_forbidden_token(t_data *data)
{
    t_token *tmp;

    tmp = *data->tokens;
    while (tmp)
    {
        if (tmp->type == TK_TYPE_AND || tmp->type == TK_TYPE_OR)
        {
            ft_printf("sorry, dont write %s we didn't do the bonus\n", tmp->val);
            free_tokens(data->tokens);
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
	//debug_create_fake_history();

	while (1)
	{
		data->line = readline("Myshell $>");
        if (!data->line)
        {
            data->exit = 1;
            data->line = ft_strdup("");
        }
        else
        {
        	data->tokens = tokenize_line(data->line);

            ft_free_and_exit_if_forbidden_token(data);
            //debug
            ft_print_tokens (data->tokens);

        }
	}
	return (0);
}










