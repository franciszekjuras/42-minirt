/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:21:54 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/18 09:13:52 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cast	obj_cast(t_object *obj, t_v3 o, t_v3 d)
{
	t_cast	cast;

	cast.obj = NULL;
	if (obj->type == SPHERE)
		return (sphere_cast(obj, obj->content, o, d));
	else if (obj->type == PLANE)
		return (plane_cast(obj, obj->content, o, d));
	else if (obj->type == CYLINDER)
		return (cylinder_cast(obj, obj->content, o, d));
	else if (obj->type == PARABOL)
		return (parabol_cast(obj, obj->content, o, d));
	else
		return (cast);
}

t_cast	closer_cast(t_cast c1, t_cast c2)
{
	if (c2.obj == NULL)
		return (c1);
	else if (c1.obj == NULL)
		return (c2);
	else if (c1.t < c2.t)
		return (c1);
	else
		return (c2);
}

t_cast	scene_cast(t_list *objs, t_v3 o, t_v3 d)
{
	t_cast		closest;

	closest.obj = NULL;
	while (objs != NULL)
	{
		closest = closer_cast(obj_cast(objs->content, o, d), closest);
		objs = objs->next;
	}
	return (closest);
}

t_cast	scene_cast_except(t_list *objs, t_object *obj, t_v3 o, t_v3 d)
{
	t_cast		closest;

	closest.obj = NULL;
	while (objs != NULL)
	{
		if (objs->content != obj)
			closest = closer_cast(obj_cast(objs->content, o, d),
					closest);
		objs = objs->next;
	}
	return (closest);
}
