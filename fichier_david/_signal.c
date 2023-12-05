// #include "../includes/minishell.h"
// /*
// void	sig_handler_sa(int signal, siginfo_t *info, void *context)
// {
// 	(void)info;
// 	(void)context;

// 	if (signal == SIGINT)
// 	{
// 		*	CTRL+C  (SIGINT)
// 		*
// 		*	on utilise 		rl_replace_line("", 0); et  rl_on_new_line();
// 		*	pour supprimer la chaine precedente (abc)
// 		*	on utilise  rl_redisplay, pour que le prompt se re-affiche aussitot
// 		*	(sinon, il faut taper du text)
	
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		printf("\n");
// 		rl_redisplay();
// 	}
// 	else if (signal == SIGQUIT)
// 	{

// 		*	CTRL+D  (SIGQUIT)
// 		*
// 		*		les caracteres   ^\    s'affichent
// 		*		"\033[2D  "	:: fait reculer le curseur de 2 et affiche 2 espaces
// 		*		"\033[2D"	:: fait reculer le curseur de 2


// 		ft_printstr("\033[2D  ");
// 		ft_printstr("\033[2D");
// 		return ;
// 	}
// }

// int	handle_signal(void)
// {
// 	struct sigaction	sa;

// 	ft_memset(&sa, 0, sizeof(sa));
// 	sa.sa_sigaction = (void *) sig_handler_sa;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// 	return (0);
// }
// */