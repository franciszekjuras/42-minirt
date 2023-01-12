/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:49:47 by jkarosas          #+#    #+#             */
/*   Updated: 2021/12/01 11:51:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	a_length;
	size_t	b_length;

	a_length = ft_strlen(src);
	b_length = ft_strlen(dst);
	a = 0;
	b = b_length;
	if (b_length < size - 1 && size > 0)
	{
		while (src[a] && b_length + a < size - 1)
		{
			dst[b] = src[a];
			a++;
			b++;
		}
		dst[b] = 0;
	}
	if (b_length >= size)
		b_length = size;
	return (a_length + b_length);
}
