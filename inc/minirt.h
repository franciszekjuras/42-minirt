/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:17:37 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/15 20:54:32 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42/MLX42.h>
# include <libgf/gf.h>
# include <input.h>

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
 * v - vector _towards_ viewer
 * 
 */
typedef struct s_cast
{
	double	t;
	t_v3	n;
	t_v3	v;
}	t_cast;

#endif
