/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:46:47 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/24 19:14:22 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft/libft.h>

int	parse_integer_params(int *arr, t_ft_argparse *arg, int num)
{
	int		i;
	int		err;
	char	*param;

	i = 0;
	while (i < num && arg->params[i] != NULL)
	{
		param = arg->params[i];
		arr[i] = ft_strtonum(&param, INT_MIN, INT_MAX, &err);
		if (err || *param != '\0')
			break ;
		++i;
	}
	if (i != num)
	{
		printf("Argument -%c requires %d valid parameters, got only %d\n",
			arg->arg, num, i);
		return (0);
	}
	return (1);
}
