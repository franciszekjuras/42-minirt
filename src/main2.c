/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:38:30 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/14 18:30:41 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include "minirt.h"
#include "input.h"

// static void	dbg_vec3(const char *prefix, t_gf_vec3 v, const char *postfix)
// {
// 	fprintf(stderr, "%s(%lf, %lf, %lf)%s", prefix, v.x, v.y, v.z, postfix);
// }

// static int	mod1_to_byte(double val)
// {
// 	return (128 + (int)(val * 127.));
// }

// static double	mod1_to_01(double val)
// {
// 	return ((val + 1.) / 2.) * 0.8 + 0.1;
// }

// static t_gf_color	vec3_to_color(t_gf_vec3 v)
// {
// 	return (gf_rgb(mod1_to_byte(v.x), mod1_to_byte(v.y), mod1_to_byte(v.z)));
// }

t_gf_color	cast_ray(t_data *data, t_gf_vec3 o, t_gf_vec3 d)
{
	t_sphere	sphere;
	t_gf_vec3	c;
	t_gf_vec3	x;
	double		r;
	double		del_sq;

	(void) data;
	sphere.origin = gf_vec3(0., 0., 0.);
	sphere.radius = 2.;
	c = sphere.origin;
	r = sphere.radius;
	x = gf_vec3_sub(o, c);
	del_sq = 4. * (gf_sq(gf_vec3_dot(d, x)) - (gf_vec3_dot(x, x) - gf_sq(r)));
	if (del_sq > 0.)
		return (gf_rgb(200, 200, 200));
	else
		return (gf_rgb(10, 10, 10));	
}

void	render(t_data *data)
{
	unsigned int	x;
	unsigned int	y;
	t_gf_vec3		ray;
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
		return(1);
	data.canvas = mlx_new_image(data.mlx, data.mlx->width, data.mlx->height);
	mlx_image_to_window(data.mlx, data.canvas, 0, 0);

	data.cam = gf_camera_new(2., gf_vec3(-3., -3., -3.), gf_vec3(1., 1., 1.));
	gf_camera_set_res(&data.cam, data.canvas->width, data.canvas->height);
	render(&data);

	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.canvas);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
