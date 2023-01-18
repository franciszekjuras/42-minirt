/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:55:19 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/18 15:40:16 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_object_list(t_list *lst)
{
	t_list		*node;
	t_list		*prev;
	t_object	*object;

	if (!lst)
		return ;
	node = lst;
	while (node)
	{
		object = node->content;
		free(object->content);
		free(node->content);
		prev = node;
		node = node->next;
		free(prev);
	}
}

static void	free_list(t_list *lst)
{
	t_list		*node;
	t_list		*prev;

	if (!lst)
		return ;
	node = lst;
	while (node)
	{
		free(node->content);
		prev = node;
		node = node->next;
		free(prev);
	}
}

void	free_scene(t_scene *scene)
{
	free_object_list(scene->objects);
	free_list(scene->lights);
	if (scene->camera)
		free(scene->camera);
	if (scene->ambient)
		free(scene->ambient);
	if (scene)
		free(scene);
}
