/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:49:41 by jkarosas          #+#    #+#             */
/*   Updated: 2021/12/01 11:51:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	a = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*s1));
	if (!a)
		return (NULL);
	while (s1[y])
	{
		a[i] = s1[y];
		i++;
		y++;
	}
	y = 0;
	while (s2[y])
	{
		a[i] = s2[y++];
		i++;
	}
	a[i] = 0;
	return (a);
}
