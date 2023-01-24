/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:42:23 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/24 16:43:53 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_camera(t_scene *scene, char **line)
{
	t_camera	*camera;
	int			error;

	error = 0;
	if (splitsize(line) != 4)
		return(cleanup("Wrong camera usage"));
	if (scene->camera != NULL)
		return(cleanup("Camera can only be declared once"));
	camera = malloc(sizeof(t_camera));
	error += parse_coordinates(&camera->origin, line[1]);
	error += parse_orientation(&camera->orientation, line[2]);
	camera->fov = ft_atoi(line[3]);
	if (camera->fov <= 0. || camera->fov > 180.)
	{
		free(camera);
		return(cleanup("FOV has to be in range [0,180]"));
	}
	scene->camera = camera;
	return (error);
}

int	parse_light(t_scene *scene, char **line)
{
	t_light	*light;
	int		error;

	error = 0;
	if (splitsize(line) != 4)
		return (cleanup("Wrong light usage\n"));
	light = malloc(sizeof(t_light));
	error += parse_coordinates(&light->origin, line[1]);
	light->brightness = ft_atof(line[2]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
	{
		free(light);
		printf("Brightness ratio has to be in range [0.0,1.0]\n");
		return (1);
	}
	error += parse_color(&light->color, line[3]);
	ft_lstadd_back(&scene->lights, ft_lstnew(light));
	return (error);
}

int	parse_ambient_lighting(t_scene *scene, char **line)
{
	t_ambient	*alighting;
	int			error;

	error = 0;
	if (splitsize(line) != 3)
		return (cleanup("Wrong ambient light usage"));
	if (scene->ambient != NULL)
		return (cleanup("Ambient light can only be declared once"));
	alighting = malloc(sizeof(t_ambient));
	alighting->brightness = ft_atof(line[1]);
	if (alighting->brightness < 0.0 || alighting->brightness > 1.0)
	{
		free(alighting);
		printf("Ambient light ratio has to be in range [0.0,1.0]\n");
		return (1);
	}
	error += parse_color(&alighting->color, line[2]);
	scene->ambient = alighting;
	return (error);
}
