/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:18:32 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/16 12:59:41 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	render_pixel(t_data *data, unsigned int x, unsigned int y)
{
	t_v3			ray;
	t_cast			cast;
	double			shade;
	t_gf_color		color;

	ray = gf_camera_ray(&data->cam, x, y);
	cast = intersection(data->scene->objects, data->cam.pos, ray);
	if (cast.obj != NULL)
	{
		shade = shader(data, cast.p, cast.n);
		color = gf_color_mult(cast.obj->color, shade);
	}
	else
		color = gf_rgb(0, 0, 0);
	mlx_put_pixel(data->canvas, x, y, gf_ctoi(color));
}

void	render(t_data *data)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < data->canvas->height)
	{
		x = 0;
		while (x < data->canvas->width)
		{
			render_pixel(data, x, y);
			++x;
		}
		++y;
	}
}
