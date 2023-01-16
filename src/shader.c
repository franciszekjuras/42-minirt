/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:29:44 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/16 13:42:05 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	shader(t_data *data, t_v3 p, t_v3 n)
{
	double	res;
	t_v3	l;

	res = data->scene->ambient->brightness;
	l = v3_norm(v3_sub(data->scene->light->origin, p));
	res += ft_fmax(0., v3_dot(l, n));
	return (res);
}
