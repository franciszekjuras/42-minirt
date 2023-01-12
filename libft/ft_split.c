/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:46:42 by jkarosas          #+#    #+#             */
/*   Updated: 2021/12/01 11:51:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char const *s, char c)
{
	int	w;
	int	i;

	w = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			w++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (w);
}

static char	*ft_get_words(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (*s && *s == c)
		s++;
	while (s[i] && s[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

static void	ft_free(int i, char **a)
{
	while (i > 0)
	{
		free(a[i - 1]);
		i--;
	}
	free(a);
}

char	**ft_split(char const *s, char c)
{
	char	**a;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = ft_size(s, c);
	a = malloc(sizeof(char *) * (words + 1));
	if (!a)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		a[i] = ft_get_words(s, c);
		if (a[i] == NULL)
			ft_free(i, a);
		while (*s && *s != c)
			s++;
		i++;
	}
	a[i] = NULL;
	return (a);
}
