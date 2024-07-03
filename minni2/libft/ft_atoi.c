/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:54:29 by welyousf          #+#    #+#             */
/*   Updated: 2023/12/09 17:05:12 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_result(unsigned long long result,
		long long sign, const char *str, int i)
{
	if (result >= 922337203685477580 && str[i] != '\0' && sign > 0)
	{
		if (str[i] == '8' || str[i] == '9')
			return (-1);
		else if (result > 922337203685477580 && ft_isdigit(str[i]))
			return (-1);
	}
	if (result >= 922337203685477580 && str[i] != '\0' && sign < 0)
	{
		if (str[i] == '9')
			return (0);
		else if (result > 922337203685477580 && ft_isdigit(str[i]))
			return (0);
	}
	return (1337);
}

int	ft_atoi(const char *str)
{
	int					i;
	long long			sign;
	unsigned long long	result;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == '+')
	{
		sign = !(str[i] == '-') - (str[i] == '-');
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (handle_result(result, sign, str, i) == -1)
			return (-1);
		if (handle_result(result, sign, str, i) == 0)
			return (0);
		result = 10 * result + (str[i] - 48);
		i++;
	}
	return (result * sign);
}
