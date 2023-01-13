/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gf_vector3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:41:33 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/19 20:41:34 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gf.h"

void	gf_vec3_ineg(t_gf_vec3 *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}

void	gf_vec3_isub(t_gf_vec3 *v1, t_gf_vec3 v2)
{
	v1->x -= v2.x;
	v1->y -= v2.y;
	v1->z -= v2.z;
}

void	gf_vec3_iadd(t_gf_vec3 *v1, t_gf_vec3 v2)
{
	v1->x += v2.x;
	v1->y += v2.y;
	v1->z += v2.z;
}

void	gf_vec3_imult(t_gf_vec3 *v, double m)
{
	v->x *= m;
	v->y *= m;
	v->z *= m;
}
