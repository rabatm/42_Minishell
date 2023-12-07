/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/07 16:39:02 by svanmarc         ###   ########.fr       */
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
    add_history("""q"" ""x""");
    add_history("echo   '   $USER  '   > output.txt | cat < input.txt ; echo Fini");
}

/*
int	main(int argc, char **argv, char **env)
{
	t_data	*data;
    //t_token **tokens;
    t_token *tmp;

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
            tmp = *data->tokens;
            while (tmp)
            {
                if (tmp->type == TK_TYPE_AND || tmp->type == TK_TYPE_OR)
                {
                    ft_printf("sorry, %s is not implemented yet\n", tmp->val);
                    free_tokens(tokens);
                    return (0);
                }
                tmp=tmp->next;
            }
            
            
        }


	}
    */


   
 void ft_print_tokens (t_token **tokens)
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


/*
void ft_free_and_exit_if_forbidden_token(data)
{



}
*/


int	main(int argc, char **argv, char **env)
{
	t_data	*data;
    //t_token **tokens;
    //t_token *tmp;

	(void)argc;
	(void)argv;
	data = init_data(env);

	//handle_signal();	// * Handle ctrl+C and ctrl+D
	debug_create_fake_history();

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

           //ft_free_and_exit_if_forbidden_token(data);

            ft_print_tokens (data->tokens);

        }
	}
	return (0);
}



/*

int main(void)
{
    char *line = "echo $USER > output.txt | cat < input.txt ; echo Fini";
	//char	*line = ">> << > < | 'ABCD' ; $";
    //char    *line = "qwerty   uio   12345";
//                       x   x
//                   0123456789
	//char	*line = "asd 'AVC' def";
    t_token **tokens;
    t_token *tmp;

    printf("Ligne de commande : %s\n", line);

    tokens = tokenize_line(line);

    printf("Tokens :\n");
    tmp = *tokens;
	int i = 0;
    while (tmp)
    {
        printf("Valeur[%d] : %s, Type : %d\n",i, tmp->val, tmp->type);
        tmp = tmp->next;
		i++;
    }

    free_tokens(tokens);

    return 0;
}
*/









