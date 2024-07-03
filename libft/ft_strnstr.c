/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:13:08 by welyousf          #+#    #+#             */
/*   Updated: 2024/06/30 11:32:18 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
int ft_strnstr2(char *cmd)
{
	char **allcmd;
	int  i;
	
	allcmd = malloc(7 * sizeof(char *));
	allcmd[0] = "echo";
	allcmd[1] = "cd";
	allcmd[2] = "pwd";
	allcmd[3] = "export";
	allcmd[4] = "unset";
	allcmd[5] = "env";
	allcmd[6] = "exit";
	i = -1;
	while (++i < 7)
	{
		if (ft_strnstr(cmd, allcmd[i], ft_strlen(allcmd[i])) != NULL)
		{
			free(allcmd);
			return 1;
		}
	}
	free(allcmd);
	return 0;
}