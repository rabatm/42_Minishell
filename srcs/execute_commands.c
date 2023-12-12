/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martincelavie <martincelavie@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:04:09 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/11 18:48:00 by martincelav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_cmd_array(t_token **tokens)
{
	int		fd;
	t_token	*tmp;

	fd = NULL;
	tmp = *tokens;
	while(tmp)
	{
		tmp = tmp->next;
	}
	return (fd);
}
