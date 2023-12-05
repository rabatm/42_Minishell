


// *	Ajoutes des lignes de tests à l'historique.
void	debug_create_fake_history(void)
{
	add_history("env | sort");
	add_history("echo ABC > _out || echo $?");
	add_history("export CC=ccccccccccc");
	add_history("export BB=bbbbbbbbbbbbbbb");
	add_history("export AA =aaaaaaaaaa");
	//...
}





int	main(int argc, char **argv, char **env)
{
	t_data	data;

	/*
	 *	- Initialise data
	 *	- Copie env dans data->env (on utilise plus le "vrai" env ensuite)
	 */
	ft_TODO_init_data(&data, env);


	handle_signal();	// * Handle ctrl+C and ctrl+D

	debug_create_fake_history();

	while (!data.exit)
	{
		data.line = readline("Mini5h3ll>");


		/*
		*	quand on fait ctrl+/, readline renvoit une chaine NULL
		*	(c'est pas la meme chose qu'une chaine vide "")
		*	On doit quitter minishell
		*/
		if (!data.line)
		{
			data->exit = 1;
			// si vous faites un free(data.line) dans la suite du prog, vous aurez un segfault: free(null)
			// data.line = ft_strdup("");

			// data->exit peut aussi etre mofifie par le buitin EXIT
		}
		else
		{
			data.tokens = parser_line_and_create_tokens(data);	// renvoit NULL si error ou chaine vide

			if (data.tokens)
			{

				/*
				 *	parcourir tous le tokens
				 *		if (token.type == TK_TYPE_STR && !token.escape_env_var)
				 *			relplace_env_vars
				 */
				ft_TODO_replace_env_vars(data)

				ft_TODO_execute_comand(data)
			}
		}
		ft_TODO_free_everything_needed_before_next_prompt(&data);	// free: line, tokens....
	}

	ft_TODO_free_everything_needed_before_exit_ms(&data);
	return (0);
}