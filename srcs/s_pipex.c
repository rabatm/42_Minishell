/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:32:02 by mrabat            #+#    #+#             */
/*   Updated: 2023/12/06 18:17:54 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipex *ft_initpipexstruc(char **argv, char **envp)
{
	t_pipex *mypipex;
	char    **path;
	
	path = ft_split(ft_getenvpath(envp), ':');
	mypipex = malloc(sizeof(t_pipex));
	mypipex->splitarg1 = ft_split(argv[2], ' ');
    mypipex->splitarg2 = ft_split(argv[3], ' ');
	mypipex->cmd1 = ft_checkexe(mypipex->splitarg1[0], path);
    mypipex->cmd2 = ft_checkexe(mypipex->splitarg2[0], path);
	free(path);
	if (pipe(mypipex->fd) == -1)
    {
        ft_printf("fail... \n");
        exit(EXIT_FAILURE);
    }
	return (mypipex);
}

void free_multi(char **v)
{
	int	i;

	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
}

void	ft_freemypex(t_pipex *mypipex)
{
	free_multi(mypipex->splitarg1);
	free_multi(mypipex->splitarg2);
	
	free(mypipex->cmd1);
	free(mypipex->cmd2);
	free(mypipex);
}
/*
function pipex
*/
void pipex(int argc, char **argv, char **env)
{


    mypipex->pid1 = fork();
    if (mypipex->pid1 < 0)
        exit(EXIT_FAILURE);
    if (mypipex->pid1 == 0)
         execve(mypipex->cmd1, mypipex->splitarg1, envp);
    mypipex->pid2 = fork();
    if (mypipex->pid2 < 0) 
        exit(EXIT_FAILURE);
    if (mypipex->pid2 == 0)
        execve(mypipex->cmd2, mypipex->splitarg2, envp);
    }
    ft_closefd(mypipex->fd);
    waitpid(mypipex->pid1, NULL, 0);
    waitpid(mypipex->pid2, NULL, 0);
    ft_freemypex(mypipex);
}