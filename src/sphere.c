/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:26:18 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/17 22:44:58 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cast	sphere_cast(t_object *obj, t_sphere *sph, t_v3 o, t_v3 d)
{
	t_cast		cast;
	t_quad_sol	sol;
	t_v3		x;

	cast.obj = NULL;
	x = v3_sub(o, sph->origin);
	sol = quad_solver_a1(v3_dot(d, x), (v3_dot(x, x) - gf_sq(sph->radius)));
	if (sol.num == 0 || sol.s1 <= 0.)
		return (cast);
	cast.obj = obj;
	cast.t = sol.s1;
	cast.p = v3_add(o, v3_mult(d, cast.t));
	cast.n = v3_mult(v3_sub(cast.p, sph->origin), 1. / sph->radius);
	return (cast);
}
