/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:17:37 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/13 21:50:11 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <MLX42/MLX42.h>
#include <libgf/gf.h>

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t *canvas;
	t_gf_camera	cam;
}	t_data;

#endif
