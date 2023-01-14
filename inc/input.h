/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:55:15 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/14 18:51:21 by fjuras           ###   ########.fr       */
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
	t_v3	origin;
	t_v3	orientation;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_v3	origin;
	double	brightness;
}	t_light;

typedef struct s_ambient
{
	t_v3	color;
	double	brightness;
}	t_ambient;

// Objects -----------------------------------

typedef struct s_plane
{
	t_v3	origin;
	t_v3	orientation;
}	t_plane;

typedef struct s_sphere
{
	t_v3	origin;
	double	radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_v3	origin;
	t_v3	orientation;
	double	radius;
	double	height;
}	t_cylinder;

typedef enum e_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_type;

typedef struct s_object
{
	void	*content;
	t_v3	color;
	t_type	type;
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