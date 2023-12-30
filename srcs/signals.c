/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:26:26 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/30 20:46:57 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', 1);
	}
	else if (signal == SIGQUIT)
	{
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
