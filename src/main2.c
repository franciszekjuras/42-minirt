/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:38:30 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/15 23:17:06 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include "minirt.h"
#include "input.h"
#include "parser.h"

// static void	dbg_vec3(const char *prefix, t_v3 v, const char *postfix)
// {
// 	fprintf(stderr, "%s(%lf, %lf, %lf)%s", prefix, v.x, v.y, v.z, postfix);
// }

double	shader(t_v3 d, t_v3 n)
{
	return (0.2 + v3_dot(d, n));
}

t_quad_sol	quad_solver(double a, double b_half, double c)
{
	t_quad_sol	sol;
	double		delta;
	double		delta_sqrt;

	sol.num = 0;
	if (a == 0.)
		return (sol);
	delta = gf_sq(b_half) - (a * c);
	if (delta <= 0.)
		return (sol);
	sol.num = 2;
	delta_sqrt = sqrt(delta);
	if (a > 0)
	{
		sol.s1 = (-b_half - delta_sqrt) / a;
		sol.s2 = (-b_half + delta_sqrt) / a;
	}
	else
	{
		sol.s1 = (-b_half + delta_sqrt) / a;
		sol.s2 = (-b_half - delta_sqrt) / a;
	}
	return (sol);
}

t_quad_sol	quad_solver_a1(double b_half, double c)
{
	t_quad_sol	sol;
	double		delta;
	double		delta_sqrt;

	sol.num = 0;
	delta = gf_sq(b_half) - c;
	if (delta <= 0.)
		return (sol);
	sol.num = 2;
	delta_sqrt = sqrt(delta);
	sol.s1 = (-b_half - delta_sqrt);
	sol.s2 = (-b_half + delta_sqrt);
	return (sol);
}


t_cast	sphere_intersection(t_object *obj, t_sphere *sph, t_v3 o, t_v3 d)
{
	t_cast		cast;
	t_quad_sol	sol;
	t_v3		x;
	t_v3		p_c;

	cast.obj = NULL;
	x = v3_sub(o, sph->origin);
	sol = quad_solver_a1(v3_dot(d, x), (v3_dot(x, x) - gf_sq(sph->radius)));
	if (sol.num == 0 || sol.s1 <= 0.)
		return (cast);
	cast.obj = obj;
	cast.t = sol.s1;
	p_c = v3_sub(v3_add(o, v3_mult(d, cast.t)), sph->origin);
	cast.n = v3_mult(p_c, 1. / sph->radius);
	return (cast);
}

t_cast	obj_intersection(t_object *obj, t_v3 o, t_v3 d)
{
	t_cast	cast;

	cast.obj = NULL;
	if (obj->type == SPHERE)
		return (sphere_intersection(obj, obj->content, o, d));
	return (cast);
}

t_cast	closer_cast(t_cast c1, t_cast c2)
{
	if (c2.obj == NULL)
		return (c1);
	else if (c1.obj == NULL)
		return (c2);
	else if (c1.t < c2.t)
		return (c1);
	else
		return (c2);
}

t_cast	intersection(t_list *objs, t_v3 o, t_v3 d)
{
	t_cast		closest;

	closest.obj = NULL;
	while (objs != NULL)
	{
		closest = closer_cast(obj_intersection(objs->content, o, d), closest);
		objs = objs->next;
	}
	return (closest);
}

void	render(t_data *data)
{
	unsigned int	x;
	unsigned int	y;
	t_v3			ray;
	t_cast			cast;
	double			shade;
	t_gf_color		color;

	y = 0;
	while (y < data->canvas->height)
	{
		x = 0;
		while (x < data->canvas->width)
		{
			ray = gf_camera_ray(&data->cam, x, y);
			cast = intersection(data->scene->objects, data->cam.pos, ray);
			if (cast.obj != NULL)
			{
				shade = shader(v3_neg(ray), cast.n);
				color = gf_color_mult(cast.obj->color, shade);
			}
			else
				color = gf_rgb(0, 0, 0);
			mlx_put_pixel(data->canvas, x, y, gf_ctoi(color));
			++x;
		}
		++y;
	}
}

int	minirt(char *filename)
{
	t_data		data;

	data.scene = parser(filename);
	if (!data.scene)
		return (1);
	data.mlx = mlx_init(800, 600, "MLX42", false);
	if (!data.mlx)
		return (1);
	data.canvas = mlx_new_image(data.mlx, data.mlx->width, data.mlx->height);
	mlx_image_to_window(data.mlx, data.canvas, 0, 0);

	data.cam = gf_camera_new(1.2, v3(-4., -4., -4.), v3(1., 1., 1.));
	gf_camera_set_res(&data.cam, data.canvas->width, data.canvas->height);
	render(&data);

	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.canvas);
	mlx_terminate(data.mlx);
	free_scene(data.scene);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage : ./miniRT *.rt\n");
		return (1);
	}
	minirt(argv[1]);
	return (0);
}
