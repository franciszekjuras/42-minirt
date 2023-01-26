/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:06:11 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/26 16:29:34 by jkarosas         ###   ########.fr       */
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

static int	rgb_check(char **split)
{
	int	i;
	int	y;
	int	dec;
	int	nul;

	i = -1;
	while (split[++i])
	{
		y = -1;
		dec = 0;
		nul = 0;
		while (split[i][++y])
		{
			if (split[i][y] == '.')
				dec++;
			else if (dec > 0)
			{
				if (split[i][y] != '0')
					nul++;
			}
		}
		if (dec > 1 || nul != 0)
			return (1);
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

	split = ft_split(line, ',');
	if (splitsize(split) != 3)
		return (cleanup_split(split, "Color usage: [R,G,B]"));
	if (rgb_check(split))
		return (cleanup_split(split, "Wrong RGB component usage"));
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
