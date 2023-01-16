/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gf_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:39:18 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/16 12:33:15 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "gf.h"

static t_v3	get_perpend_vec_in_xy_plane(t_v3 v)
{
	v.z = 0;
	v = v3_norm(v);
	return (v3(v.y, -v.x, 0));
}

t_gf_camera	gf_camera_new(int fov_deg, t_v3 pos, t_v3 dir)
{
	t_gf_camera	cam;

	cam.fov_scale_px = 0;
	cam.mid_height_px = 0;
	cam.mid_width_px = 0;
	cam.fov = ((double)fov_deg) * GF_DEG ;
	cam.pos = pos;
	cam.z = v3_norm(dir);
	cam.x = get_perpend_vec_in_xy_plane(cam.z);
	cam.y = v3_cross(cam.z, cam.x);
	return (cam);
}

void	gf_camera_set_res(t_gf_camera *cam, int width_px, int height_px)
{
	cam->mid_height_px = height_px / 2;
	cam->mid_width_px = width_px / 2;
	cam->fov_scale_px = (double) width_px;
}

t_v3	gf_camera_ray(t_gf_camera *cam, int x_px, int y_px)
{
	t_v3	ray;
	double	fov_mult;

	x_px -= cam->mid_width_px;
	y_px -= cam->mid_height_px;
	fov_mult = cam->fov / cam->fov_scale_px;
	ray = cam->z;
	v3_iadd(&ray, v3_mult(cam->x, fov_mult * (double) x_px));
	v3_iadd(&ray, v3_mult(cam->y, fov_mult * (double) y_px));
	return (v3_norm(ray));
}
