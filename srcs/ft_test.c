/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:34:59 by mrabat            #+#    #+#             */
/*   Updated: 2023/12/31 00:45:33 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getcmd(char *arg)
{
	return (ft_strjoin("/usr/bin/", arg));
}

char	**ft_getenvpath(char **envp)
{
	int		b_find;
	int		i;
	char	**t_path;
	char	*tmp_slip;

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
		printf(RED": ERROR ENV VARIBLES\n"RST);
		exit(1);
	}
	tmp_slip = envp[i - 1] + 5;
	t_path = ft_split(tmp_slip, ':');
	return (t_path);
}

char	*ft_checkexe(char *cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*for_exe;

	i = 0;
	while (path[i])
	{
		for_exe = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(for_exe, cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(for_exe);
			return (tmp);
		}
		free(for_exe);
		free(tmp);
		i++;
	}
	return (NULL);
}
