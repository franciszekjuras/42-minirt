/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:06:11 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/28 15:45:33 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parser.h"

static int	orientation_check(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		if (is_atof_abs_just_gt_1(split[i]))
			return (1);
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
	if (!isfinite(point->x) || !isfinite(point->x) || !isfinite(point->x))
		return (cleanup_split(split, "Invalid coordinate argument"));
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
	if (!isfinite(point->x) || point->x < -1 || point->x > 1
		|| !isfinite(point->y) || point->y < -1 || point->y > 1
		|| !isfinite(point->z) || point->z < -1 || point->z > 1
		|| orientation_check(split))
	{
		return (cleanup_split(split,
				"Invalid orientation vector value"));
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
