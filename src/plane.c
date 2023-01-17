/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:47:16 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/17 22:37:21 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"

t_cast	plane_intersection(t_object *obj, t_plane *pln, t_v3 o, t_v3 d)
{
	t_cast	cast;
	t_v3	x;
	double	denom;

	cast.obj = NULL;
	denom = v3_dot(pln->orientation, d);
	x = v3_sub(pln->origin, o);
	cast.t = v3_dot(x, pln->orientation) / denom;
	if (cast.t >= 0)
	{
		cast.obj = obj;
		cast.p = v3_add(o, v3_mult(d, cast.t));
		if (denom < 0)
			cast.n = pln->orientation;
		else
			cast.n = v3_mult(pln->orientation, -1.0);
	}
	return (cast);
}
