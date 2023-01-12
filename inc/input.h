/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:55:15 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/12 14:51:48 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "stdio.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"

// Vector ------------------------------------

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// Camera and lighting -----------------------

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	orientation;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	origin;
	double	brightness;
}	t_light;

typedef struct s_ambient
{
	t_vec3	color;
	double	brightness;
}	t_ambient;

// Objects -----------------------------------

typedef struct s_plane
{
	t_vec3	origin;
	t_vec3	orientation;
}	t_plane;

typedef struct s_sphere
{
	t_vec3	origin;
	double	radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3	origin;
	t_vec3	orientation;
	double	radius;
	double	height;
}	t_cylinder;

typedef enum e_type
{
	PLANE, SPHERE, CYLINDER
}	t_type;

typedef struct s_object
{
	void	*content;
	t_vec3	color;
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