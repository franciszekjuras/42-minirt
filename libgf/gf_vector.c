/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gf_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:41:24 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/19 20:41:24 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gf.h"

t_v3	v3(double x, double y, double z)
{
	t_v3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_v3	v3_neg(t_v3 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

t_v3	v3_sub(t_v3 v1, t_v3 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_v3	v3_add(t_v3 v1, t_v3 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_v3	v3_mult(t_v3 v, double m)
{
	v.x *= m;
	v.y *= m;
	v.z *= m;
	return (v);
}
