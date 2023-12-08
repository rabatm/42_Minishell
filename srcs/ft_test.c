/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:34:59 by mrabat            #+#    #+#             */
/*   Updated: 2023/12/06 17:55:17 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_initoutfile(char *filename)
{
	int fdfile;

	fdfile = open(filename, O_WRONLY | O_CREAT, 0777);
	dup2(fdfile,STDOUT_FILENO);
	return (fdfile);
}

int	ft_initinfile(char *filename)
{
	int fdfile;

	fdfile = open(filename, O_RDONLY );
	dup2(fdfile,STDIN_FILENO);
	return (fdfile);
}

char	*ft_getcmd(char *arg)
{
	return ft_strjoin("/usr/bin/",arg);
}

char    *ft_getenvpath(char **envp)
{
	int b_find;
	int i;

	b_find = 0;
	i = 0;
	while (envp[i] && b_find == 0)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			b_find = 1;
		i++;
	}
	if (b_find == 0) 
	{
		ft_putstr_fd("ERORR ENV VARIBLES",2);
		exit(1);
	}
	return (envp[i-1] + 5);
}

void	ft_closefd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

char	*ft_checkexe(char *for_exe, char **path)
{

 	char	*tmp_exe;
	int	chk_result;
	int	i;
		
	i = 0;
	chk_result = -1;
	while (path[i] && chk_result)
	{
		tmp_exe = ft_strjoin(ft_strjoin(path[i], "/"), for_exe);
		chk_result = ft_check_file_exist(tmp_exe);
		i++;
	}
	if (chk_result == -1)
	{
		ft_putstr_fd(for_exe,2);     
		ft_putstr_fd(": command not found",2);     
		exit(EXIT_FAILURE);
	}
	return (tmp_exe);
}