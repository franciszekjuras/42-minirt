/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:44:42 by jkarosas          #+#    #+#             */
/*   Updated: 2021/12/01 11:51:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_length(int n)
{
	size_t	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n != 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*a;
	size_t	len;
	long	num;	

	len = ft_length(n);
	a = (char *)malloc(len + 1);
	if (a == NULL)
		return (NULL);
	num = n;
	if (n < 0)
	{
		num = -num;
		a[0] = '-';
	}
	if (num == 0)
		a[0] = '0';
	a[len] = '\0';
	while (num != 0)
	{
		a[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (a);
}
