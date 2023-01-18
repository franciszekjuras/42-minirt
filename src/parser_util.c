/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:06:01 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/18 14:15:05 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	compare(char c)
{
	if (ft_isdigit(c) || c == '.' || c == ',' || c == '-' || c == '\n')
		return (0);
	return (1);
}

int	check_line(char **split)
{
	int	i;
	int	y;

	i = 1;
	while (split[i])
	{
		y = 0;
		while (split[i][y])
		{
			if (compare(split[i][y]))
				return (1);
			y++;
		}
		i++;
	}
	return (0);
}
