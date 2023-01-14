/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:55:15 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/14 17:49:44 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "stdio.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <libgf/gf.h>
# include <libft/libft.h>

// Camera and lighting -----------------------

typedef struct s_camera
{
	t_gf_vec3	origin;
	t_gf_vec3	orientation;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_gf_vec3	origin;
	double		brightness;
}	t_light;

typedef struct s_ambient
{
	t_gf_vec3	color;
	double		brightness;
}	t_ambient;

// Objects -----------------------------------

typedef struct s_plane
{
	t_gf_vec3	origin;
	t_gf_vec3	orientation;
}	t_plane;

typedef struct s_sphere
{
	t_gf_vec3	origin;
	double		radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_gf_vec3	origin;
	t_gf_vec3	orientation;
	double		radius;
	double		height;
}	t_cylinder;

typedef enum e_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_type;

typedef struct s_object
{
	void		*content;
	t_gf_vec3	color;
	t_type		type;
}	t_object;

// Scene -------------------------------------

typedef struct s_scene
{
	t_camera	*camera;
	t_light		*light;
	t_ambient	*ambient;
	t_list		*objects;
}	t_scene;

#endif