/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:02:58 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/27 16:20:50 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parser.h"

int	parse_plane(t_scene *scene, char **line)
{
	t_plane		*plane;
	t_object	*object;
	int			error;

	error = 0;
	if (splitsize(line) != 4)
	{
		printf("Wrong plane usage\n");
		return (1);
	}
	plane = malloc(sizeof(t_plane));
	object = malloc(sizeof(t_object));
	error += parse_coordinates(&plane->origin, line[1]);
	error += parse_orientation(&plane->orientation, line[2]);
	error += parse_color(&object->color, line[3]);
	object->content = plane;
	object->type = PLANE;
	ft_lstadd_back(&scene->objects, ft_lstnew(object));
	return (error);
}

int	parse_sphere(t_scene *scene, char **line)
{
	t_sphere	*sphere;
	t_object	*object;
	int			error;

	error = 0;
	if (splitsize(line) != 4)
	{
		printf("Wrong sphere usage\n");
		return (1);
	}
	sphere = malloc(sizeof(t_sphere));
	object = malloc(sizeof(t_object));
	error += parse_coordinates(&sphere->origin, line[1]);
	sphere->radius = ft_atof(line[2]) / 2;
	if (!isfinite(sphere->radius) || sphere->radius <= 0.)
	{
		object->content = sphere;
		ft_lstadd_back(&scene->objects, ft_lstnew(object));
		return (printf("Sphere must have positive diameter\n"));
	}
	error += parse_color(&object->color, line[3]);
	object->content = sphere;
	object->type = SPHERE;
	ft_lstadd_back(&scene->objects, ft_lstnew(object));
	return (error);
}

int	parse_cylinder(t_scene *scene, char **line)
{
	t_cylinder	*cylinder;
	t_object	*object;
	int			error;

	error = 0;
	if (splitsize(line) != 6)
		return (printf("Wrong cylinder usage\n"));
	cylinder = malloc(sizeof(t_cylinder));
	object = malloc(sizeof(t_object));
	error += parse_coordinates(&cylinder->origin, line[1]);
	error += parse_orientation(&cylinder->orientation, line[2]);
	cylinder->radius = ft_atof(line[3]) / 2;
	cylinder->height = ft_atof(line[4]);
	if (!isfinite(cylinder->radius) || cylinder->height <= 0.
		|| !isfinite(cylinder->height) || cylinder->radius <= 0.)
	{
		object->content = cylinder;
		ft_lstadd_back(&scene->objects, ft_lstnew(object));
		return (printf("Cylinder must have positive diameter and height\n"));
	}
	error += parse_color(&object->color, line[5]);
	object->content = cylinder;
	object->type = CYLINDER;
	ft_lstadd_back(&scene->objects, ft_lstnew(object));
	return (error);
}

int	parse_parabol(t_scene *scene, char **line)
{
	t_parabol	*prb;
	t_object	*object;
	int			error;

	error = 0;
	if (splitsize(line) != 7)
		return (printf("Wrong paraboloid usage\n"));
	prb = malloc(sizeof(t_parabol));
	object = malloc(sizeof(t_object));
	object->content = prb;
	object->type = PARABOL;
	error += parse_coordinates(&prb->origin, line[1]);
	error += parse_orientation(&prb->orientation, line[2]);
	prb->focus = ft_atof(line[3]);
	prb->bottom = ft_atof(line[4]);
	prb->top = ft_atof(line[5]);
	if (!isfinite(prb->focus) || !isfinite(prb->bottom) || !isfinite(prb->top)
		|| prb->focus <= 0. || prb->bottom < 0. || prb->top <= prb->bottom)
	{
		ft_lstadd_back(&scene->objects, ft_lstnew(object));
		return (printf("Invalid paraboloid specification\n"));
	}
	error += parse_color(&object->color, line[6]);
	ft_lstadd_back(&scene->objects, ft_lstnew(object));
	return (error);
}
