/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martincelavie <martincelavie@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:39:12 by hchauvin          #+#    #+#             */
/*   Updated: 2023/11/14 16:36:11 by martincelav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10

char	*read_str(int fd, char *str)
{
	char	*buff;
	int		read_size;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_size = 1;
	while (ft_strchr(str, '\n') == 0 && read_size != 0 && str)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_size] = '\0';
		str = ft_strjoin_free(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_line(char *str)
{
	char	*tab;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	tab = ft_calloc((i + 2), sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		tab[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		tab[i] = str[i];
		i++;
	}
	return (tab);
}

char	*next_line(char *str)
{
	char	*tab;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	tab = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!tab)
		return (NULL);
	j = 0;
	i++;
	while (str[i])
		tab[j++] = str[i++];
	tab[j] = '\0';
	free(str);
	return (tab);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		if (str[i])
			str[i] = NULL;
		i++;
	}
}

char	*get_next_line(int fd, int last)
{
	char		*line;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		ft_free(str);
		return (NULL);
	}
	if (!str[fd])
		str[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str[fd])
		return (NULL);
	str[fd] = read_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_line(str[fd]);
	str[fd] = next_line(str[fd]);
	if ((!str[fd]) || last == 1)
		free(str[fd]);
	return (line);
}

#endif