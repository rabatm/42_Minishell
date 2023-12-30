/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_strs_tools_3.c.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:15:52 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 16:14:37 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**free_tab_and_return_null(char **tab)
{
	ft_free_tab(tab);
	return (NULL);
}

char	**ft_add_str_to_tab(t_data *data, char *entry)
{
	int		i;
	char	**new;

	i = 0;
	while (data->env[i])
		i++;
	new = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		new[i] = ft_strdup(data->env[i]);
		if (!new[i])
			return (free_tab_and_return_null(new));
		i++;
	}
	new[i] = ft_strdup(entry);
	if (!new[i])
		return (free_tab_and_return_null(new));
	return (new);
}
