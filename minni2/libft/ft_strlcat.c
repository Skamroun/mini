/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 00:20:26 by welyousf          #+#    #+#             */
/*   Updated: 2023/12/20 21:35:27 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calclen(char	*dst, size_t	*odstsize)
{
	size_t	dstlen;

	dstlen = 0;
	while (dst[dstlen] != '\0' && *odstsize > 0)
	{
		dstlen++;
		(*odstsize)--;
	}
	return (dstlen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	x;
	size_t	dstlen;
	size_t	odstsize;

	odstsize = dstsize;
	dstlen = calclen(dst, &odstsize);
	if (odstsize == 0 && dst[dstlen] != '\0')
		return (ft_strlen(src) + dstsize);
	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize > dstlen)
	{
		while (i < dstsize - dstlen - 1 && *(src + i) != '\0')
		{
			*(dst + dstlen + i) = *(src + i);
			i++;
		}
	}
	*(dst + dstlen + i) = '\0';
	x = dstlen >= dstsize;
	return (ft_strlen(src) + (1 - x) * dstlen + x * dstsize);
}
