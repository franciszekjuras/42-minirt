/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:06:11 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/24 19:14:44 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		|| point->z < -1 || point->z > 1)
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

	split = ft_split(line, ',');
	if (splitsize(split) != 3)
		return (cleanup_split(split, "Color usage: [R,G,B]"));
	color->r = ft_atof(split[0]);
	color->g = ft_atof(split[1]);
	color->b = ft_atof(split[2]);
	if (color->r < 0. || color->g < 0. || color->b < 0.
		|| color->r > 255. || color->g > 255. || color->b > 255.)
	{
		return (cleanup_split(split,
				"RGB components must be in range [0, 255]"));
	}
	free_split(split);
	return (0);
}
