/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchauvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:18:15 by hchauvin          #+#    #+#             */
/*   Updated: 2023/05/15 10:20:01 by hchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	tmp1 = dest;
	tmp2 = (unsigned char *)src;
	if (dest < src)
		return (ft_memcpy(dest, src, len));
	if (dest > src)
		while (len--)
			tmp1[len] = tmp2[len];
	return (dest);
}
