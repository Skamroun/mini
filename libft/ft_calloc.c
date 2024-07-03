/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:47:50 by welyousf          #+#    #+#             */
/*   Updated: 2023/12/09 15:48:41 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if ((count == 0) || (size == 0))
	{
		str = malloc(0);
		return (str);
	}
	if ((long long)(count) < 0 || (long long)(size) < 0)
		return (NULL);
	if ((9223372036854775807) / count < size)
		return (NULL);
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}
