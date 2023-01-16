/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:29:44 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/16 14:00:13 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	shader(t_data *data, t_cast cast)
{
	double	res;
	t_v3	light;
	double	light_dist;
	t_cast	shadow_cast;

	res = data->scene->ambient->brightness;
	light = v3_sub(data->scene->light->origin, cast.p);
	light_dist = v3_len(light);
	light = v3_mult(light, 1. / light_dist);
	shadow_cast = intersection_except(data->scene->objects,
		cast.obj, cast.p, light);
	if (shadow_cast.obj == NULL || shadow_cast.t > light_dist)
		res += ft_fmax(0., v3_dot(light, cast.n));
	return (res);
}
