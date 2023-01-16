/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:17:37 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/16 18:49:42 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42/MLX42.h>
# include <libgf/gf.h>
# include "input.h"

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*canvas;
	t_gf_camera	cam;
	t_scene		*scene;
}	t_data;

/**
 * t - distance from viewr
 * n - normal vector 
 * obj - object pointer
 */
typedef struct s_cast
{
	double		t;
	t_v3		n;
	t_v3		p;
	t_object	*obj;
}	t_cast;

typedef struct s_quad_sol
{
	int		num;
	double	s1;
	double	s2;
}	t_quad_sol;

/*sphere*/
t_cast		sphere_intersection(t_object *obj,
				t_sphere *sph, t_v3 o, t_v3 d);

/*plane*/
t_cast	plane_intersection(t_object *obj,
				t_plane *pln, t_v3 o, t_v3 d);

/*intersection.c*/
t_cast		obj_intersection(t_object *obj, t_v3 o, t_v3 d);
t_cast		closer_cast(t_cast c1, t_cast c2);
t_cast		intersection(t_list *objs, t_v3 o, t_v3 d);
t_cast		intersection_except(t_list *objs, t_object *obj, t_v3 o, t_v3 d);
/*quad_solver.c*/
t_quad_sol	quad_solver(double a, double b_half, double c);
t_quad_sol	quad_solver_a1(double b_half, double c);
/*render.c*/
void		render(t_data *data);
/*shader.c*/
double		shader(t_data *data, t_cast cast);

#endif
