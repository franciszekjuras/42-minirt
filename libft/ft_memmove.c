/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:46:05 by jkarosas          #+#    #+#             */
/*   Updated: 2021/12/01 11:51:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	char	*a;
	char	*b;

	a = (char *)dest;
	b = (char *)src;
	if (a > b)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			a[i] = b[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)n)
		{
			a[i] = b[i];
			i++;
		}
	}
	return (dest);
}
