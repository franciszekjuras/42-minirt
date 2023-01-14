/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:38:30 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/14 18:49:45 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include "minirt.h"
#include "input.h"

// static void	dbg_vec3(const char *prefix, t_v3 v, const char *postfix)
// {
// 	fprintf(stderr, "%s(%lf, %lf, %lf)%s", prefix, v.x, v.y, v.z, postfix);
// }

t_gf_color	cast_ray(t_data *data, t_v3 o, t_v3 d)
{
	t_sphere	sphere;
	t_v3		c;
	t_v3		x;
	double		r;
	double		del_sq;

	(void) data;
	sphere.origin = v3(0., 0., 0.);
	sphere.radius = 2.;
	c = sphere.origin;
	r = sphere.radius;
	x = v3_sub(o, c);
	del_sq = 4. * (gf_sq(v3_dot(d, x)) - (v3_dot(x, x) - gf_sq(r)));
	if (del_sq > 0.)
		return (gf_rgb(200, 200, 200));
	else
		return (gf_rgb(10, 10, 10));
}

void	render(t_data *data)
{
	unsigned int	x;
	unsigned int	y;
	t_v3			ray;
	t_gf_color		color;

	y = 0;
	while (y < data->canvas->height)
	{
		x = 0;
		while (x < data->canvas->width)
		{
			ray = gf_camera_ray(&data->cam, x, y);
			color = cast_ray(data, data->cam.pos, ray);
			mlx_put_pixel(data->canvas, x, y, gf_ctoi(color));
			++x;
		}
		++y;
	}
}

int	main(void)
{
	t_data		data;

	data.mlx = mlx_init(800, 600, "MLX42", false);
	if (!data.mlx)
		return (1);
	data.canvas = mlx_new_image(data.mlx, data.mlx->width, data.mlx->height);
	mlx_image_to_window(data.mlx, data.canvas, 0, 0);

	data.cam = gf_camera_new(2., v3(-3., -3., -3.), v3(1., 1., 1.));
	gf_camera_set_res(&data.cam, data.canvas->width, data.canvas->height);
	render(&data);

	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.canvas);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
