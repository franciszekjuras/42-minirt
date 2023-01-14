/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gf.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:41:47 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/14 18:24:11 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GF_H
# define GF_H

# define GF_PI 3.14159265358979323846
# define GF_DEG 0.0174532925199432957692
# define GF_INVDEG 57.2957795130823208768

typedef struct s_gf_point
{
	int	x;
	int	y;
}	t_gf_point;

typedef struct s_gf_vec3
{
	double	x;
	double	y;
	double	z;
}	t_gf_vec3;

typedef struct s_gf_camera
{
	t_gf_vec3	pos;
	t_gf_vec3	x;
	t_gf_vec3	y;
	t_gf_vec3	z;
	double		fov;
	double		fov_scale_px;
	int			mid_height_px;
	int			mid_width_px;
}	t_gf_camera;

typedef struct s_gf_color
{
	int	b;
	int	g;
	int	r;
	int	a;
}	t_gf_color;

typedef struct s_gf_grad
{
	t_gf_color	beg;
	t_gf_color	end;
	double		va;
	double		vr;
	double		vg;
	double		vb;
	double		ibeg;
	double		iend;
}	t_gf_grad;

/*gf_color.c*/
int			gf_ctoi(t_gf_color color);
t_gf_color	gf_rgb(int r, int g, int b);
t_gf_color	gf_hsl(double h, double s, double l);
t_gf_color	gf_hsv(double h, double s, double v);
/*gf_strtodouble.c*/
double		gf_strtodouble(char **npp);
/*gf_grad.c*/
t_gf_grad	gf_grad(t_gf_color beg, t_gf_color end, double ibeg, double iend);
t_gf_color	gf_color_grad(double i, t_gf_grad *grad);
/*gf_vector.c*/
t_gf_vec3	gf_vec3(double x, double y, double z);
t_gf_vec3	gf_vec3_neg(t_gf_vec3 v);
t_gf_vec3	gf_vec3_sub(t_gf_vec3 v1, t_gf_vec3 v2);
t_gf_vec3	gf_vec3_add(t_gf_vec3 v1, t_gf_vec3 v2);
t_gf_vec3	gf_vec3_mult(t_gf_vec3 v, double m);
double		gf_vec3_dot(t_gf_vec3 v1, t_gf_vec3 v2);
t_gf_vec3	gf_vec3_cross(t_gf_vec3 v1, t_gf_vec3 v2);
double		gf_vec3_len(t_gf_vec3 v);
t_gf_vec3	gf_vec3_norm(t_gf_vec3 v);
void		gf_vec3_ineg(t_gf_vec3 *v);
void		gf_vec3_isub(t_gf_vec3 *v1, t_gf_vec3 v2);
void		gf_vec3_iadd(t_gf_vec3 *v1, t_gf_vec3 v2);
void		gf_vec3_imult(t_gf_vec3 *v, double m);
/*gf_camera.c*/
t_gf_camera	gf_camera_new(double fov, t_gf_vec3 pos, t_gf_vec3 dir);
void		gf_camera_set_res(t_gf_camera *cam, int width_px, int height_px);
t_gf_vec3	gf_camera_ray(t_gf_camera *cam, int x_px, int y_px);
/*gf_utils.c*/
double		gf_sq(double v);

#endif
