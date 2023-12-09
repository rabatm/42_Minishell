/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martincelavie <martincelavie@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:34:59 by mrabat            #+#    #+#             */
/*   Updated: 2023/12/09 17:39:59 by martincelav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getcmd(char *arg)
{
	return ft_strjoin("/usr/bin/",arg);
}

char    **ft_getenvpath(char **envp)
{
	int b_find;
	int i;
	char	**t_path;

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
	t_path = ft_split(envp[i-1] + 5, ':');
	return (t_path);
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
		return (NULL);
	}
	return (tmp_exe);
}