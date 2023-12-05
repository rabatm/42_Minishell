/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:21 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/05 17:37:49 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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
      //      data->tokens = 
        }


	}





	return (0);
}




