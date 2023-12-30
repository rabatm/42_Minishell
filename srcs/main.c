/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarie <mmarie@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 15:14:51 by mmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	debug_create_fake_history(void)
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
	add_history("echo abc def'ghi jkl'mno");
	add_history("echo --$USER-ABCD");
	add_history("echo \"--$USER-ABCD\"");
	add_history("echo AA--$?--$USER--");
}

void	merge_tokens_if_no_space_before(t_token **tokens)
{
	t_token	*tmp;
	char	*merged_val;
	t_token	*next_token;

	tmp = *tokens;
	tmp = tmp->next;
	while (tmp && tmp->next)
	{
		next_token = tmp->next;
		if (tmp->next->space_before == 0 && tmp->next->type == TK_TYPE_STR)
		{
			merged_val = ft_strjoin(tmp->val, next_token->val);
			free(tmp->val);
			free(next_token->val);
			tmp->val = merged_val;
			next_token = tmp->next;
			tmp->next = next_token->next;
			if (tmp->next)
				tmp->next->previous = tmp;
			free(next_token);
		}
		else
			tmp = tmp->next;
	}
}

void	print_tokens(t_token **tokens)
{
	t_token *tmp;
	if (tokens)
	{
		tmp = *tokens;
		printf(Y "------------------------------\n");
		while (tmp)
		{
		printf("Valeur : %10s \t Type : %10d   \t   change_env_var= %5d \n", tmp->val, tmp->type, tmp->change_env_var);
			tmp = tmp->next;
		}
		printf("------------------------------" RST "\n");
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

void	free_and_exit_if_forbidden_token(t_data *data)
{
	t_token *tmp;

	tmp = *data->tokens;
	while (tmp)
	{
		if (tmp->type == TK_TYPE_AND || tmp->type == TK_TYPE_OR)
		{
			printf(RED "sorry, dont write [%s] we didn't do the bonus\n" RST, tmp->val);
			break;
		}
		tmp=tmp->next;
	}
	if (tmp)
	{
		free_data(data);
		exit(0);
	}
}

int	main(int argc, char **argv, char **env)
{
	//test_ft_str_replace();
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

            // if (!data->tokens)
            //     continue;
            if (data->tokens && *data->tokens)
            {
                free_and_exit_if_forbidden_token(data);
                replace_env_var(data);
                merge_tokens_if_no_space_before(data->tokens);
                ft_exec(data);
            }
            else
                continue;

           // free_and_exit_if_forbidden_token(data);
            //print_tokens (data->tokens);
          //  replace_env_var(data);
            //print_tokens (data->tokens);
           // merge_tokens_if_no_space_before(data->tokens);
            print_tokens (data->tokens);

            //print_tokens (data->tokens);
           // ft_exec(data);
            //free_tokens(data->tokens);
        }
        // free(data->line);
        // data->line = NULL;
        // if (data->exit == 1)
        //     break;
	}
    free_data(data);
	return (0);
}
