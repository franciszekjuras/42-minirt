/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:21:54 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/15 23:26:50 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cast	obj_intersection(t_object *obj, t_v3 o, t_v3 d)
{
	t_cast	cast;

	cast.obj = NULL;
	if (obj->type == SPHERE)
		return (sphere_intersection(obj, obj->content, o, d));
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

t_cast	intersection(t_list *objs, t_v3 o, t_v3 d)
{
	t_cast		closest;

	closest.obj = NULL;
	while (objs != NULL)
	{
		closest = closer_cast(obj_intersection(objs->content, o, d), closest);
		objs = objs->next;
	}
	return (closest);
}
