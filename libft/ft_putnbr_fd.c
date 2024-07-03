/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:18:37 by welyousf          #+#    #+#             */
/*   Updated: 2023/12/20 21:48:19 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	x;

	x = n;
	if (x < 0)
	{
		x = -x;
		ft_putchar_fd('-', fd);
	}
	if (x >= 10)
		ft_putnbr_fd(x / 10, fd);
	ft_putchar_fd((x % 10) + 48, fd);
}
