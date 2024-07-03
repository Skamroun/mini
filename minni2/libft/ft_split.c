/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:04:13 by welyousf          #+#    #+#             */
/*   Updated: 2023/12/20 21:49:36 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countwords(char *str, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		while (str[i] != '\0' && str[i] != c)
			i++;
		count++;
	}
	i = (i > 0 && str[i - 1] == c);
	return (count - i);
}

static size_t	ft_countletters(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void	ft_free(char **str, size_t i)
{
	while (i-- > 0)
		free(str[i]);
	free(str);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**str;
	size_t	i;

	if (!s)
		return (NULL);
	words = countwords((char *)s, c);
	str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s != '\0' && *s == c)
			s++;
		str[i] = ft_substr((char *)s, 0, ft_countletters((char *)s, c));
		if (!str[i])
		{
			ft_free(str, i);
			return (NULL);
		}
		s = s + ft_strlen(str[i++]);
	}
	str[i] = NULL;
	return (str);
}
