/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:18:32 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/19 22:03:31 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	render_pixel(t_data *data, unsigned int x, unsigned int y)
{
	t_v3			ray;
	t_cast			cast;
	t_gf_color		color;

	ray = gf_camera_ray(&data->cam, x, y);
	cast = scene_cast(data->scene->objects, data->cam.pos, ray);
	if (cast.obj != NULL)
		color = shader(data, cast, v3_neg(ray));
	else
		color = gf_rgb(0, 0, 0);
	gf_img_pxput(&data->ctx.img, x, y, gf_ctoi(color));
}

void	render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->ctx.h)
	{
		x = 0;
		while (x < data->ctx.w)
		{
			render_pixel(data, x, y);
			++x;
		}
		++y;
	}
	gf_img_put(&data->ctx, &data->ctx.img);
}
