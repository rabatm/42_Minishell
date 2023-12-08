#include "../includes/minishell.h"

void	sig_handler_sa(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	} else if (signal == SIGQUIT)
	{
		printf("\033[2D  ");
		printf("\033[2D");
		return;
	}
}

int	handle_signal(void)
{
	struct sigaction sa;
	
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &sig_handler_sa;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return -1;
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return -1;
	}
	return (0);
}

