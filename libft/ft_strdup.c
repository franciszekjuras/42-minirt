/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:49:31 by jkarosas          #+#    #+#             */
/*   Updated: 2021/12/01 11:51:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*a;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	a = (char *)malloc(sizeof(*s) * (i + 1));
	if (!a)
		return (NULL);
	i = 0;
	while (s[i])
	{
		a[i] = s[i];
		i++;
	}
	a[i] = 0;
	return (a);
}
