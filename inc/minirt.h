/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:17:37 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/15 16:06:08 by jkarosas         ###   ########.fr       */
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

#endif
