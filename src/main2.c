/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:38:30 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/15 23:41:15 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include "minirt.h"
#include "parser.h"

int	minirt(char *filename)
{
	t_data		data;

	data.scene = parser(filename);
	if (!data.scene)
		return (1);
	data.mlx = mlx_init(800, 600, "MLX42", false);
	if (!data.mlx)
		return (1);
	data.canvas = mlx_new_image(data.mlx, data.mlx->width, data.mlx->height);
	mlx_image_to_window(data.mlx, data.canvas, 0, 0);

	data.cam = gf_camera_new(1.2, v3(-4., -4., -4.), v3(1., 1., 1.));
	gf_camera_set_res(&data.cam, data.canvas->width, data.canvas->height);
	render(&data);

	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.canvas);
	mlx_terminate(data.mlx);
	free_scene(data.scene);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage : ./miniRT *.rt\n");
		return (1);
	}
	minirt(argv[1]);
	return (0);
}
