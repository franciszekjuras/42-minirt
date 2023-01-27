/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtonum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:03:34 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/27 15:27:14 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_strptonum(
				char **npp, long long min, long long max, int *err)
{
	long long	r;

	*err = 0;
	r = ft_strtoll_e(*npp, npp, 10, err);
	if (r < min)
	{
		r = min;
		*err |= FT_STRTOI_OVERFLOW;
	}
	else if (r > max)
	{
		r = max;
		*err |= FT_STRTOI_OVERFLOW;
	}
	return (r);
}

long long	ft_strtonum(
				char *np, long long min, long long max, int *err)
{
	long long	r;

	r = ft_strptonum(&np, min, max, err);
	if (*err)
		return (r);
	while (ft_isspace(*np))
		++np;
	if (*np != '\0')
		*err = FT_STRTOI_INVCHAR;
	return (r);
}
