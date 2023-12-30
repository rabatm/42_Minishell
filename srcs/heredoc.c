/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:57:28 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 23:59:07 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int apply_redirection_in_delim(t_data *data, t_token *token)
{
    int     fd;
    char    *line;
    char    *delim;

    if (data->heredoc_handled == 1)
        unlink(".heredoc");
    else if (ft_rediretion_error(data, token))
        return (1);
    delim = token->next->val;
    fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (handle_error_fd(data, token, fd));
    redirection_dilem2(fd, line, delim);
    close(fd);
    data->heredoc_handled = 1;
    return (0);
}

int redirection_dilem2(int fd, char *line, char *delim)
{
    while (1)
    {
        line = readline("> ");
        if (!line)
            break ;
        if (ft_strcmp(line, delim) == 0)
        {
            free(line);
            break ;
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
    }
}
