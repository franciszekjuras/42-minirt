/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:38:30 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/15 21:45:34 by jkarosas         ###   ########.fr       */
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

double	sphere_intersection(t_v3 o, t_v3 d, t_sphere sphere)
{
	t_v3		c;
	t_v3		x;
	double		r;
	double		delta;
	double		t;
	double		b2;

	c = sphere.origin;
	r = sphere.radius;
	x = v3_sub(o, c);
	b2 = v3_dot(d, x);
	delta = 4. * (gf_sq(b2) - (v3_dot(x, x) - gf_sq(r)));
	if (delta <= 0.)
		return (-1);
	t = quad_smaller_pos_sol(-b2, sqrt(delta) / 2.);
	if (t <= 0.)		
		return (-1);
	return (t);
}

t_gf_color	intersection(t_data *data, t_v3 o, t_v3 d)
{
	t_list		*objects;
	t_object	*closest;
	t_object	*object;
	double		t_min;
	double		t;

	t_v3		p_c;
	t_v3		normal;
	double		shade;

	t_min = INFINITY;
	closest = NULL;
	objects = data->scene->objects;
	t = -1;
	while (objects != NULL)
	{
		object = objects->content;
		if (object->type == SPHERE)
			t = sphere_intersection(o, d, *(t_sphere *)object->content);
		if (t > 0 && t < t_min)
		{
			closest = object;
			t_min = t;
		}
		objects = objects->next;
	}
	if (closest == NULL)
		return (gf_rgb(0, 0, 0));
	t_sphere sphere = *(t_sphere *)closest->content;
	p_c = v3_sub(v3_add(o, v3_mult(d, t_min)), sphere.origin);
	normal = v3_norm(p_c);
	shade = shader(data, d, normal);
	return (gf_color_mult(gf_rgb(closest->color.x, closest->color.y, closest->color.z), shade));
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
			color = intersection(data, data->cam.pos, ray);
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

	data.cam = gf_camera_new(2., v3(-3., -3., -3.), v3(1., 1., 1.));
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
		printf("Usage : ./miniRT *.rt");
		return (1);
	}
	minirt(argv[1]);
	return (0);
}
