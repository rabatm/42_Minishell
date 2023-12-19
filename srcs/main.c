/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/19 11:13:06 by svanmarc         ###   ########.fr       */
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
    add_history(", ,, . .. | || & && ; ;; ( ) < << > >> $");
    add_history("""q""""x""");
    add_history("echo   '   $USER  '   > output.txt | cat < input.txt ; echo Fini");
    add_history("echo abc def'ghi jkl");



}
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
            return;
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
    debug_create_fake_history();
	//handle_signal();	// * Handle ctrl+C and ctrl+D
	while (1)
	{
		//handle_signal();
		data->line = readline("Myshell $>");

        // ***** line  : [       echo     "aaa"  "$USER"'$USER']

		if (!data->line)
		{
		    data->exit = 1;
		    data->line = ft_strdup("");
		}
        else
        {
            add_history(data->line);
        	data->tokens = tokenize_line(data->line);

            /*
                         escape_env_var    space_before
                echo        0                1
                aaa         0                1
                $USER       0                1
                $USER       1                0
            */


            if (!data->tokens)
                continue;
            //free_and_exit_if_forbidden_token(data);
            //print_tokens (data->tokens);

            replace_env_var(data);


         /*
                             space_before
                echo           1
                aaa            1
                sva            1
                $USER          0
            */


            /*
            merge_tokens_with_no_space_before(data);

                parcourir tokens
                    if (token nest pas le 1er et que token->space_before == 1)
                        fusionner ce token avec celui d'avant
                        supprimer ce token
            */


            /*
                echo
                aaa
                sva$USER
            */




            print_tokens (data->tokens);
            ft_exec(data);
            free_tokens(data->tokens);
        }
	}
	return (0);
}
