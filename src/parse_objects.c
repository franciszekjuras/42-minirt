/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:02:58 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/24 16:35:44 by jkarosas         ###   ########.fr       */
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
		return (printf("Wrong cylinder usage\n"));
	cylinder = malloc(sizeof(t_cylinder));
	object = malloc(sizeof(t_object));
	error += parse_coordinates(&cylinder->origin, line[1]);
	error += parse_orientation(&cylinder->orientation, line[2]);
	cylinder->radius = ft_atof(line[3]) / 2;
	cylinder->height = ft_atof(line[4]);
	if (cylinder->height < 0 || cylinder->radius < 0)
	{
		object->content = cylinder;
		ft_lstadd_back(&scene->objects, ft_lstnew(object));
		return (printf("Cylinders cannot have negative diameter or height\n"));
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
	error += parse_coordinates(&prb->origin, line[1]);
	error += parse_orientation(&prb->orientation, line[2]);
	prb->focus = ft_atof(line[3]);
	prb->bottom = ft_atof(line[4]);
	prb->top = ft_atof(line[5]);
	if (prb->focus <= 0. || prb->bottom < 0. || prb->top <= prb->bottom)
	{
		object->content = prb;
		ft_lstadd_back(&scene->objects, ft_lstnew(object));
		return (printf("Invalid paraboloid specification\n"));
	}
	error += parse_color(&object->color, line[6]);
	object->content = prb;
	object->type = PARABOL;
	ft_lstadd_back(&scene->objects, ft_lstnew(object));
	return (error);
}
