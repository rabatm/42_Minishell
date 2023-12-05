/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchauvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:41:30 by hchauvin          #+#    #+#             */
/*   Updated: 2023/05/15 13:03:35 by hchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	strt;
	size_t	end;
	char	*result;

	strt = 0;
	if (!s1 || !set)
		return (0);
	end = ft_strlen(s1);
	while (s1[strt] && ft_strchr(set, s1[strt]))
		strt++;
	while (end && s1[end - 1] && ft_strchr(set, s1[end - 1]))
		end--;
	if (strt > end)
		return (ft_strdup(""));
	result = ft_substr(s1, strt, end - strt);
	return (result);
}
