/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:38:30 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/14 20:09:30 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include "minirt.h"
#include "input.h"

// static void	dbg_vec3(const char *prefix, t_v3 v, const char *postfix)
// {
// 	fprintf(stderr, "%s(%lf, %lf, %lf)%s", prefix, v.x, v.y, v.z, postfix);
// }

double	quad_smaller_pos_sol(double const_term, double sign_term)
{
	double	sol1;
	double	sol2;

	sol1 = const_term - sign_term;
	sol2 = const_term + sign_term;
	if (sol1 < sol2)
	{
		if (sol1 > 0)
			return (sol1);
		else
			return (sol2);
	}
	else
	{
		if (sol2 > 0)
			return (sol2);
		else
			return (sol1);
	}
}

double	shader(t_data *data, t_v3 d, t_v3 n)
{
	(void)data;
	(void)d;
	(void)n;
	return (0.2 - v3_dot(d, n));
}

t_gf_color	cast_ray(t_data *data, t_v3 o, t_v3 d)
{
	t_sphere	sphere;
	t_v3		c;
	t_v3		x;
	t_v3		p_c;
	t_v3		normal;
	double		r;
	double		delta;
	double		t;
	double		b2;
	double		shade;

	sphere.origin = v3(0., 0., 0.);
	sphere.radius = 2.;
	c = sphere.origin;
	r = sphere.radius;
	x = v3_sub(o, c);
	b2 = v3_dot(d, x);
	delta = 4. * (gf_sq(b2) - (v3_dot(x, x) - gf_sq(r)));
	if (delta <= 0.)
		return (gf_rgb(0, 0, 0));
	t = quad_smaller_pos_sol(-b2, sqrt(delta) / 2.);
	if (t <= 0.)		
		return (gf_rgb(0, 0, 0));
	p_c = v3_sub(v3_add(o, v3_mult(d, t)), c);
	normal = v3_norm(p_c);
	shade = shader(data, d, normal);
	return (gf_color_mult(gf_rgb(255, 200, 200), shade));
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
	mlx_terminate(data.mlx);
	return (0);
}
