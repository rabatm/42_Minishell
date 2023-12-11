/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:26:26 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/11 16:33:19 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
*/

static void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putchar_fd('\n', 1);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		// My terminal doesn't do this, so I won't do it.
		// ft_printstr("\033[2D  ");
		// ft_printstr("\033[2D");
		// return ;
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}

int	handle_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = (void *)sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (0);
}

// int	main(void)
// {
// 	handle_signal();
// 	pause();
// 	return 0;
// }