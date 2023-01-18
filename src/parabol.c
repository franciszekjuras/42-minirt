/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parabol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:26:18 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/18 09:33:05 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_par_qtx	calc_par_ctx(t_parabol *par, t_v3 o, t_v3 d)
{
	t_par_qtx	q;
	double		d_dot_v;
	double		x_dot_v;

	q.c = par->origin;
	q.v = par->orientation;
	q.m_max = par->top;
	q.m_min = par->bottom;
	q.x = v3_sub(o, par->origin);
	d_dot_v = v3_dot(d, q.v);
	x_dot_v = v3_dot(q.x, q.v);
	q.sol = quad_solver(v3_dot(d, d) - gf_sq(d_dot_v),
			v3_dot(d, q.x) - d_dot_v * (x_dot_v + 2 * par->focus),
			v3_dot(q.x, q.x) - x_dot_v * (x_dot_v + 4 * par->focus));
	if (q.sol.num == 0)
		return (q);
	q.p_c1 = v3_add(v3_mult(d, q.sol.s1), q.x);
	q.p_c2 = v3_add(v3_mult(d, q.sol.s2), q.x);
	q.m1 = v3_dot(q.p_c1, q.v);
	q.m2 = v3_dot(q.p_c2, q.v);
	return (q);
}

static t_cast	par_cap(t_object *obj, const t_par_qtx *q, t_v3 o, t_v3 d)
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
		cap.origin = v3_add(q->c, v3_mult(q->v, q->m_min));
	}
	return (plane_cast(obj, &cap, o, d));
}

static t_cast	par_side(t_object *obj, t_parabol *par, const t_par_qtx *q)
{
	t_cast	cast;

	if (q->sol.s1 <= 0)
	{
		cast.obj = NULL;
		return (cast);
	}
	cast.t = q->sol.s1;
	cast.p = v3_add(par->origin, q->p_c1);
	cast.n = v3_norm(v3_sub(q->p_c1, v3_mult(q->v, q->m1 + par->focus)));
	cast.obj = obj;
	return (cast);
}

t_cast	parabol_cast(t_object *obj, t_parabol *par, t_v3 o, t_v3 d)
{
	t_cast		cast;
	t_par_qtx	q;

	cast.obj = NULL;
	q = calc_par_ctx(par, o, d);
	if (q.sol.num == 0 || (q.m1 <= q.m_min && q.m2 <= q.m_min)
		|| (q.m1 >= q.m_max && q.m2 >= q.m_max))
		return (cast);
	if (q.m1 > q.m_min && q.m1 < q.m_max)
		return (par_side(obj, par, &q));
	else
		return (par_cap(obj, &q, o, d));
}
