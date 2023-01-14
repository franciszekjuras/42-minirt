/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gf_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:41:29 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/14 18:38:50 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "gf.h"

double	v3_dot(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_v3	v3_cross(t_v3 v1, t_v3 v2)
{	
	t_v3	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

double	v3_len(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_v3	v3_norm(t_v3 v)
{
	t_v3	r;
	double	len;

	len = v3_len(v);
	if (len == 0.)
		return (v3(1., 0., 0.));
	r.x = v.x / len;
	r.y = v.y / len;
	r.z = v.z / len;
	return (r);
}
