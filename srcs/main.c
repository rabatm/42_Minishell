/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/07 15:05:50 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
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
        }


	}





	return (0);
}*/





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









