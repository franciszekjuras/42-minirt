/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:29:44 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/18 16:47:31 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

static double	calc_specular_factor(double l_dot_n,
							t_v3 light, t_v3 normal, t_v3 viewer)
{
	t_v3	reflection;
	double	r_dot_v;

	reflection = v3_sub(v3_mult(normal, 2. * l_dot_n), light);
	r_dot_v = v3_dot(reflection, viewer);
	if (r_dot_v > 0.)
		return (0.5 * pow(r_dot_v, 8.));
	else
		return (0.);
}

static void	add_spot_light(t_gf_color *res,
		t_cast cast, t_spot_ctx s, t_v3 viewer)
{
	t_gf_color	uniform;
	t_gf_color	specular;
	double		specular_factor;

	uniform = gf_color_ch_mult(cast.obj->color, s.light->color,
			s.l_dot_n * s.light->brightness);
	specular_factor = calc_specular_factor(s.l_dot_n, s.l, cast.n, viewer);
	specular = gf_color_mult(s.light->color,
			specular_factor * s.light->brightness);
	gf_color_iadd(res, uniform);
	gf_color_iadd(res, specular);
}

t_gf_color	shader(t_data *data, t_cast cast, t_v3 viewer)
{
	t_list		*lights;
	t_gf_color	res;
	t_spot_ctx	s;

	lights = data->scene->lights;
	res = gf_color_ch_mult(cast.obj->color,
			data->scene->ambient->color, data->scene->ambient->brightness);
	while (lights != NULL)
	{
		s.light = lights->content;
		s.l = v3_sub(s.light->origin, cast.p);
		s.l_dist = v3_len(s.l);
		s.l = v3_mult(s.l, 1. / s.l_dist);
		s.l_dot_n = v3_dot(s.l, cast.n);
		if (s.l_dot_n > 0.)
		{
			s.shadow_cast = scene_cast_except(data->scene->objects,
					cast.obj, cast.p, s.l);
			if (s.shadow_cast.obj == NULL || s.shadow_cast.t > s.l_dist)
				add_spot_light(&res, cast, s, viewer);
		}
		lights = lights->next;
	}
	return (res);
}
