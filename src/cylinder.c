/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:26:18 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/19 19:48:20 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_cyl_qtx	calc_cyl_ctx(t_cylinder *cyl, t_v3 o, t_v3 d)
{
	t_cyl_qtx	q;
	double		d_dot_v;
	double		x_dot_v;

	q.c = cyl->origin;
	q.v = cyl->orientation;
	q.x = v3_sub(o, q.c);
	d_dot_v = v3_dot(d, q.v);
	x_dot_v = v3_dot(q.x, q.v);
	q.m_max = cyl->height;
	q.quad_c = v3_dot(q.x, q.x) - gf_sq(x_dot_v) - gf_sq(cyl->radius);
	q.sol = quad_solver(1. - gf_sq(d_dot_v),
			v3_dot(d, q.x) - (d_dot_v * x_dot_v), q.quad_c);
	if (q.sol.num <= 0)
		return (q);
	q.p_c1 = v3_add(v3_mult(d, q.sol.s1), q.x);
	q.p_c2 = v3_add(v3_mult(d, q.sol.s2), q.x);
	q.m1 = v3_dot(q.p_c1, q.v);
	q.m2 = v3_dot(q.p_c2, q.v);
	return (q);
}

static t_cast	cyl_cap(t_object *obj, const t_cyl_qtx *q, t_v3 o, t_v3 d)
{
	t_plane	cap;

	if (q->m1 >= q->m_max)
	{
		cap.orientation = q->v;
		cap.origin = v3_add(q->c, v3_mult(q->v, q->m_max));
	}
	else
	{
		cap.orientation = v3_neg(q->v);
		cap.origin = q->c;
	}
	return (plane_cast(obj, &cap, o, d));
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

static t_cast	cyl_parallel(t_object *obj, const t_cyl_qtx *q, t_v3 o, t_v3 d)
{
	t_plane	cap;
	t_cast	cast;

	if (q->quad_c > 0.)
	{
		cast.obj = NULL;
		return (cast);
	}
	if (v3_dot(q->v, d) < 0.)
	{
		cap.orientation = q->v;
		cap.origin = v3_add(q->c, v3_mult(q->v, q->m_max));
	}
	else
	{
		cap.orientation = v3_neg(q->v);
		cap.origin = q->c;
	}
	return (plane_cast(obj, &cap, o, d));
}

t_cast	cylinder_cast(t_object *obj, t_cylinder *cyl, t_v3 o, t_v3 d)
{
	t_cast		cast;
	t_cyl_qtx	q;

	cast.obj = NULL;
	q = calc_cyl_ctx(cyl, o, d);
	if (q.sol.num < 0)
		return (cyl_parallel(obj, &q, o, d));
	if (q.sol.num == 0 || (q.m1 <= 0. && q.m2 <= 0.)
		|| (q.m1 >= q.m_max && q.m2 >= q.m_max))
		return (cast);
	if (q.m1 > 0. && q.m1 < q.m_max)
		return (cyl_side(obj, cyl, &q));
	else
		return (cyl_cap(obj, &q, o, d));
}
