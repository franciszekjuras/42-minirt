/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:26:18 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/15 23:26:38 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cast	sphere_intersection(t_object *obj, t_sphere *sph, t_v3 o, t_v3 d)
{
	t_cast		cast;
	t_quad_sol	sol;
	t_v3		x;
	t_v3		p_c;

	cast.obj = NULL;
	x = v3_sub(o, sph->origin);
	sol = quad_solver_a1(v3_dot(d, x), (v3_dot(x, x) - gf_sq(sph->radius)));
	if (sol.num == 0 || sol.s1 <= 0.)
		return (cast);
	cast.obj = obj;
	cast.t = sol.s1;
	p_c = v3_sub(v3_add(o, v3_mult(d, cast.t)), sph->origin);
	cast.n = v3_mult(p_c, 1. / sph->radius);
	return (cast);
}
