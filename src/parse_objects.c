/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:02:58 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/12 15:18:51 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	{
		printf("Wrong cylinder usage\n");
		return (1);
	}
	cylinder = malloc(sizeof(t_cylinder));
	object = malloc(sizeof(t_object));
	error += parse_coordinates(&cylinder->origin, line[1]);
	error += parse_orientation(&cylinder->orientation, line[2]);
	cylinder->radius = ft_atof(line[3]) / 2;
	cylinder->height = ft_atof(line[4]);
	if (cylinder->height < 0 || cylinder->radius < 0)
	{
		printf("Cylinders can not have a diameter or height that is negative\n");
		return (1);
	}
	error += parse_color(&object->color, line[5]);
	object->content = cylinder;
	object->type = CYLINDER;
	ft_lstadd_back(&scene->objects, ft_lstnew(object));
	return (error);
}
