/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:55:13 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/12 15:25:57 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parser_test(t_scene *scene)
{
	t_list		*lst = scene->objects;
	t_object	*object;

	if (scene->camera)
	{
		printf("C %f,%f,%f %f,%f,%f %i\n", scene->camera->origin.x, scene->camera->origin.y, scene->camera->origin.z,
		scene->camera->orientation.x, scene->camera->orientation.y, scene->camera->orientation.z,
		scene->camera->fov);
	}
	if (scene->light)
	{
		printf("L %f,%f,%f %f\n", scene->light->origin.x, scene->light->origin.y, scene->light->origin.z,
		scene->light->brightness);
	}
	if (scene->ambient)
	{
		printf("A %f %f,%f,%f\n", scene->ambient->brightness,
		scene->ambient->color.x, scene->ambient->color.y, scene->ambient->color.z);
	}
	while (lst)
	{
		object = lst->content;
		if (object->type == PLANE)
		{
			t_plane	*plane;
			plane = object->content;
			printf("pl %f,%f,%f %f,%f,%f %f,%f,%f\n", plane->origin.x, plane->origin.y, plane->origin.z,
			plane->orientation.x, plane->orientation.y, plane->orientation.z,
			object->color.x, object->color.y, object->color.z);
		}
		else if (object->type == SPHERE)
		{
			t_sphere	*sphere;
			sphere = object->content;
			printf("sp %f,%f,%f %f %f,%f,%f\n", sphere->origin.x, sphere->origin.y, sphere->origin.z,
			sphere->radius *2, object->color.x, object->color.y, object->color.z);
		}
		else if (object->type == CYLINDER)
		{
			t_cylinder	*cylinder;
			cylinder = object->content;
			printf("cy %f,%f,%f %f,%f,%f %f %f %f,%f,%f\n", cylinder->origin.x, cylinder->origin.y, cylinder->origin.z,
			cylinder->orientation.x, cylinder->orientation.y, cylinder->orientation.z,
			cylinder->radius * 2, cylinder->height, object->color.x, object->color.y, object->color.z);
		}
		lst = lst->next;
	}
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
	{
		printf("Usage : ./miniRT scene.rt\n");
		return (1);
	}
	scene = parser(argv[1]);
	if (!scene)
		return (1);
	parser_test(scene);
	free_scene(scene);
	return (0);
}
