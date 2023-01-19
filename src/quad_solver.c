/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:27:17 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/19 19:32:18 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

static t_quad_sol	make_unsolved(int n)
{
	t_quad_sol	sol;

	sol.num = n;
	return (sol);
}

t_quad_sol	quad_solver(double a, double b_half, double c)
{
	t_quad_sol	sol;
	double		delta;
	double		delta_sqrt;

	if (a == 0.)
		return (make_unsolved(-1));
	delta = gf_sq(b_half) - (a * c);
	if (delta <= 0.)
		return (make_unsolved(0));
	sol.num = 2;
	delta_sqrt = sqrt(delta);
	if (a > 0)
	{
		sol.s1 = (-b_half - delta_sqrt) / a;
		sol.s2 = (-b_half + delta_sqrt) / a;
	}
	else
	{
		sol.s1 = (-b_half + delta_sqrt) / a;
		sol.s2 = (-b_half - delta_sqrt) / a;
	}
	return (sol);
}

t_quad_sol	quad_solver_a1(double b_half, double c)
{
	t_quad_sol	sol;
	double		delta;
	double		delta_sqrt;

	sol.num = 0;
	delta = gf_sq(b_half) - c;
	if (delta <= 0.)
		return (sol);
	sol.num = 2;
	delta_sqrt = sqrt(delta);
	sol.s1 = (-b_half - delta_sqrt);
	sol.s2 = (-b_half + delta_sqrt);
	return (sol);
}
