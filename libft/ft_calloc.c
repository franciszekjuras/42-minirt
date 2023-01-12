/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:44:01 by jkarosas          #+#    #+#             */
/*   Updated: 2021/12/01 11:51:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*a;
	size_t	i;

	a = malloc(nmemb * size);
	if (!a)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		a[i] = '\0';
		i++;
	}
	return (a);
}
