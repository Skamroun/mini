/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:04:43 by welyousf          #+#    #+#             */
/*   Updated: 2023/12/20 21:26:46 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long x)
{
	size_t	count;

	if (x == 0)
		return (1);
	count = 0;
	if (x < 0)
	{
		x = -x;
		count++;
	}
	while (x >= 10)
	{
		x = x / 10;
		count++;
	}
	return (count + 1);
}

static char	*handelnegative(long n)
{
	int		count;
	int		ocount;
	char	*str;

	count = ft_count(n);
	ocount = count;
	n = -n;
	str = (char *)malloc(sizeof(char) * count + 1);
	if (!str)
		return (NULL);
	str[0] = '-';
	while (count > 1)
	{
		count--;
		str[count] = (n % 10 + 48);
		n = n / 10;
	}
	str[ocount] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		count;
	int		ocount;
	char	*str;
	long	x;

	x = n;
	if (n < 0)
	{
		str = handelnegative(x);
		return (str);
	}
	count = ft_count(x);
	ocount = count;
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	while (count-- > 0)
	{
		str[count] = ((x % 10) + 48);
		x = x / 10;
	}
	str[ocount] = '\0';
	return (str);
}
