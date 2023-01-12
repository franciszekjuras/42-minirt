/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:50:01 by jkarosas          #+#    #+#             */
/*   Updated: 2021/12/01 11:51:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*a;
	size_t	i;

	if (!s || !f)
		return (NULL);
	a = ft_strdup(s);
	if (!a)
		return (NULL);
	i = 0;
	while (a[i])
	{
		a[i] = f(i, a[i]);
		i++;
	}
	return (a);
}
