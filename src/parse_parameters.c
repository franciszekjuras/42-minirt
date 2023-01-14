/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:06:11 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/14 17:45:41 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_coordinates(t_v3 *point, char *line)
{
	char	**split;

	split = ft_split(line, ',');
	if (splitsize(split) != 3)
	{
		printf("Coordinate usage [x,y,z]\n");
		return (1);
	}
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
	{
		printf("Orientation usage [x,y,z]\n");
		return (1);
	}
	point->x = ft_atof(split[0]);
	point->y = ft_atof(split[1]);
	point->z = ft_atof(split[2]);
	if (point->x < -1 || point->x > 1
		|| point->y < -1 || point->y > 1
		|| point->z < -1 || point->z > 1)
	{
		printf("Orientation vector values have to be in range [-1,1]\n");
		return (1);
	}
	free_split(split);
	return (0);
}

int	parse_color(t_v3 *color, char *line)
{
	char	**split;

	split = ft_split(line, ',');
	if (splitsize(split) != 3)
	{
		printf("Colot usage [R,G,B]\n");
		return (1);
	}
	color->x = ft_atof(split[0]);
	color->y = ft_atof(split[1]);
	color->z = ft_atof(split[2]);
	if (color->x < 0 || color->x > 255
		|| color->y < 0 || color->y > 255
		|| color->z < 0 || color->z > 255)
	{
		printf("RGB components have to be in range [0,255]\n");
		return (1);
	}
	free_split(split);
	return (0);
}
