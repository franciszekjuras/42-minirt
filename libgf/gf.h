/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gf.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:41:47 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/16 12:36:45 by fjuras           ###   ########.fr       */
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

typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}	t_v3;

typedef struct s_gf_camera
{
	t_v3	pos;
	t_v3	x;
	t_v3	y;
	t_v3	z;
	double	fov;
	double	fov_scale_px;
	int		mid_height_px;
	int		mid_width_px;
}	t_gf_camera;

/**
 * r, g, b fields are in [0, 255] range
 * a (alpha channel) is [0, 1], 0 is transparent, 1 is opaque
 */
typedef struct s_gf_color
{
	double	r;
	double	g;
	double	b;
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
t_gf_color	gf_rgb(double r, double g, double b);
t_gf_color	gf_color_mult(t_gf_color color, double mult);
/*gf_strtodouble.c*/
double		gf_strtodouble(char **npp);
/*gf_vector.c*/
t_v3		v3(double x, double y, double z);
t_v3		v3_neg(t_v3 v);
t_v3		v3_sub(t_v3 v1, t_v3 v2);
t_v3		v3_add(t_v3 v1, t_v3 v2);
t_v3		v3_mult(t_v3 v, double m);
double		v3_dot(t_v3 v1, t_v3 v2);
t_v3		v3_cross(t_v3 v1, t_v3 v2);
double		v3_len(t_v3 v);
t_v3		v3_norm(t_v3 v);
void		v3_ineg(t_v3 *v);
void		v3_isub(t_v3 *v1, t_v3 v2);
void		v3_iadd(t_v3 *v1, t_v3 v2);
void		v3_imult(t_v3 *v, double m);
/*gf_camera.c*/
t_gf_camera	gf_camera_new(int fov_deg, t_v3 pos, t_v3 dir);
void		gf_camera_set_res(t_gf_camera *cam, int width_px, int height_px);
t_v3		gf_camera_ray(t_gf_camera *cam, int x_px, int y_px);
/*gf_utils.c*/
double		gf_sq(double v);

#endif
