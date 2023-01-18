/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:29:44 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/18 09:32:18 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

double	specular_factor(double l_dot_n, t_v3 light, t_v3 normal, t_v3 viewer)
{
	t_v3	reflection;
	double	r_dot_v;

	reflection = v3_sub(v3_mult(normal, 2. * l_dot_n), light);
	r_dot_v = v3_dot(reflection, viewer);
	if (r_dot_v > 0.)
		return (pow(r_dot_v, 8.));
	else
		return (0.);
}

double	shader(t_data *data, t_cast cast, t_v3 viewer)
{
	double	res;
	t_v3	light;
	double	light_dist;
	double	light_dot_normal;
	t_cast	shadow_cast;

	(void) viewer;
	res = data->scene->ambient->brightness;
	light = v3_sub(data->scene->light->origin, cast.p);
	light_dist = v3_len(light);
	light = v3_mult(light, 1. / light_dist);
	light_dot_normal = v3_dot(light, cast.n);
	if (light_dot_normal > 0.)
	{
		shadow_cast = scene_cast_except(data->scene->objects,
				cast.obj, cast.p, light);
		if (shadow_cast.obj == NULL || shadow_cast.t > light_dist)
		{
			res += light_dot_normal * data->scene->light->brightness;
			res += specular_factor(light_dot_normal, light, cast.n, viewer)
				* data->scene->light->brightness;
		}
	}
	return (res);
}
