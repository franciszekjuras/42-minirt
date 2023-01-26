/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:06:11 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/26 17:08:33 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	orientation_check(char **split)
{
	int	i;
	int	y;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '1')
			y = 2;
		else if (split[i][0] == '-' && split[i][1] == '1')
			y = 3;
		else
			y = -1;
		while (split[i][y])
		{
			if (split[i][y] != '0')
				return (1);
			y++;
		}
		i++;
	}
	return (0);
}

int	parse_coordinates(t_v3 *point, char *line)
{
	char	**split;

	split = ft_split(line, ',');
	if (splitsize(split) != 3)
		return (cleanup_split(split, "Coordinate usage: [x,y,z]"));
	point->x = ft_atof(split[0]);
	point->y = ft_atof(split[1]);
	point->z = ft_atof(split[2]);
	free_split(split);
	return (0);
}

int	parse_orientation(t_v3 *point, char *line)
{
	char	**split;

	split = ft_split(line, ',');
	if (splitsize(split) != 3)
		return (cleanup_split(split, "Orientation usage: [x,y,z]"));
	point->x = ft_atof(split[0]);
	point->y = ft_atof(split[1]);
	point->z = ft_atof(split[2]);
	if (point->x < -1 || point->x > 1
		|| point->y < -1 || point->y > 1
		|| point->z < -1 || point->z > 1
		|| orientation_check(split))
	{
		return (cleanup_split(split,
				"Orientation vector values have to be in range [-1,1]"));
	}
	if (point->x == 0. && point->y == 0. && point->z == 0.)
		return (cleanup_split(split, "Orientation vector must be non-zero"));
	*point = v3_norm(*point);
	free_split(split);
	return (0);
}

int	parse_color(t_gf_color *color, char *line)
{
	char	**split;
	int		err[3];

	split = ft_split(line, ',');
	if (splitsize(split) != 3)
		return (cleanup_split(split, "Color usage: [R,G,B]"));
	color->r = ft_strtonum(split[0], 0, 255, &err[0]);
	color->g = ft_strtonum(split[1], 0, 255, &err[1]);
	color->b = ft_strtonum(split[2], 0, 255, &err[2]);
	if (err[0] || err[1] || err[2])
	{
		return (cleanup_split(split, "Wrong RGB component usage"));
	}
	free_split(split);
	return (0);
}
