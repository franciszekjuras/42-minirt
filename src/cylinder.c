/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:26:18 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/16 22:45:48 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_cyl_qtx	calc_cyl_ctx(t_cylinder *cyl, t_v3 o, t_v3 d)
{
	t_cyl_qtx	q;

	q.v = cyl->orientation;
	q.m_max = cyl->height;
	q.x = v3_sub(o, cyl->origin);
	q.sol = quad_solver(v3_dot(d, d) - gf_sq(v3_dot(d, q.v)),
			v3_dot(d, q.x) - (v3_dot(d, q.v) * v3_dot(q.x, q.v)),
			v3_dot(q.x, q.x) - gf_sq(v3_dot(q.x, q.v)) - gf_sq(cyl->radius));
	if (q.sol.num == 0)
		return (q);
	q.p_c1 = v3_add(v3_mult(d, q.sol.s1), q.x);
	q.p_c2 = v3_add(v3_mult(d, q.sol.s2), q.x);
	q.m1 = v3_dot(q.p_c1, q.v);
	q.m2 = v3_dot(q.p_c2, q.v);
	return (q);
}

static t_cast	cyl_cap(t_object *obj, const t_cyl_qtx *q, t_v3 o, t_v3 d)
{
	t_cast	cast;

	(void) obj;
	(void) q;
	(void) o;
	(void) d;
	cast.obj = NULL;
	return (cast);
}

static t_cast	cyl_side(t_object *obj, t_cylinder *cyl, const t_cyl_qtx *q)
{
	t_cast	cast;

	if (q->sol.s1 <= 0)
	{
		cast.obj = NULL;
		return (cast);
	}
	cast.t = q->sol.s1;
	cast.p = v3_add(cyl->origin, q->p_c1);
	cast.n = v3_mult(v3_sub(q->p_c1, v3_mult(q->v, q->m1)), 1. / cyl->radius);
	cast.obj = obj;
	return (cast);
}

t_cast	cylinder_intersection(t_object *obj, t_cylinder *cyl, t_v3 o, t_v3 d)
{
	t_cast		cast;
	t_cyl_qtx	q;

	cast.obj = NULL;
	q = calc_cyl_ctx(cyl, o, d);
	if (q.sol.num == 0 || (q.m1 <= 0. && q.m2 <= 0.)
		|| (q.m1 >= q.m_max && q.m2 >= q.m_max))
		return (cast);
	if (q.m1 > 0. && q.m1 < q.m_max)
		return (cyl_side(obj, cyl, &q));
	else
		return (cyl_cap(obj, &q, o, d));
}
