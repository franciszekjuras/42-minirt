/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:17:37 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/19 22:48:12 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx/mlx.h>
# include <libgf/gf.h>
# include "input.h"

typedef struct s_data
{
	t_gf_ctx	ctx;
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

typedef struct s_cyl_qtx
{
	t_quad_sol	sol;
	t_v3		x;
	t_v3		c;
	t_v3		v;
	t_v3		p_c1;
	t_v3		p_c2;
	double		quad_c;
	double		m1;
	double		m2;
	double		m_max;
	int			parallel_hit;
}	t_cyl_qtx;

typedef struct s_par_qtx
{
	t_quad_sol	sol;
	t_v3		x;
	t_v3		c;
	t_v3		v;
	t_v3		p_c1;
	t_v3		p_c2;
	double		m1;
	double		m2;
	double		m_max;
	double		m_min;
}	t_par_qtx;

typedef struct s_spot_ctx
{
	t_light		*light;
	t_v3		l;
	double		l_dist;
	double		l_dot_n;
	t_cast		shadow_cast;
}	t_spot_ctx;

/*specific object casts*/
t_cast		sphere_cast(t_object *obj, t_sphere *sph, t_v3 o, t_v3 d);
t_cast		plane_cast(t_object *obj, t_plane *pln, t_v3 o, t_v3 d);
t_cast		cylinder_cast(t_object *obj, t_cylinder *cyl, t_v3 o, t_v3 d);
t_cast		parabol_cast(t_object *obj, t_parabol *par, t_v3 o, t_v3 d);

/*cast.c*/
t_cast		obj_cast(t_object *obj, t_v3 o, t_v3 d);
t_cast		closer_cast(t_cast c1, t_cast c2);
t_cast		scene_cast(t_list *objs, t_v3 o, t_v3 d);
t_cast		scene_cast_except(t_list *objs, t_object *obj, t_v3 o, t_v3 d);
/*quad_solver.c*/
t_quad_sol	quad_solver(double a, double b_half, double c);
t_quad_sol	quad_solver_a1(double b_half, double c);
/*render.c*/
void		render(t_data *data);
/*shader.c*/
t_gf_color	shader(t_data *data, t_cast cast, t_v3 viewer);
/*hooks.c*/
int			close_app(t_gf_ctx *ctx);
int			handle_key(int keycode, t_gf_ctx *ctx);
/*utils.c*/
void		parse_integer_params(int *arr, t_ft_argparse *arg, int num);

#endif
