/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:42:23 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/18 15:18:43 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_camera(t_scene *scene, char **line)
{
	t_camera	*camera;
	int			error;

	error = 0;
	if (splitsize(line) != 4)
	{
		printf("Wrong camera usage\n");
		return (1);
	}
	if (scene->camera != NULL)
	{
		printf("Camera can only be declared once\n");
		return (1);
	}
	camera = malloc(sizeof(t_camera));
	error += parse_coordinates(&camera->origin, line[1]);
	error += parse_orientation(&camera->orientation, line[2]);
	camera->fov = ft_atoi(line[3]);
	if (camera->fov < 0 || camera->fov > 180)
	{
		printf("FOV has to be in range [0,180]\n");
		return (1);
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
	{
		printf("Wrong light usage\n");
		return (1);
	}
	light = malloc(sizeof(t_light));
	error += parse_coordinates(&light->origin, line[1]);
	light->brightness = ft_atof(line[2]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
	{
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
	{
		printf("Wrong ambient lighting usage\n");
		return (1);
	}
	if (scene->ambient != NULL)
	{
		printf("Ambient lighting can only be declared once\n");
		return (1);
	}
	alighting = malloc(sizeof(t_ambient));
	alighting->brightness = ft_atof(line[1]);
	if (alighting->brightness < 0.0 || alighting->brightness > 1.0)
	{
		printf("Ambient ligh ratio has to be in range [0.0,1.0]\n");
		return (1);
	}
	error += parse_color(&alighting->color, line[2]);
	scene->ambient = alighting;
	return (error);
}
