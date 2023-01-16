/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:38:30 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/16 18:43:47 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include "minirt.h"
#include "parser.h"

void	hook(void *param)
{
	static int	height = 0;
	static int	width = 0;
	t_data		*data;

	data = param;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	// 	mlx_close_window(data->mlx);
	if (data->mlx->height != height || data->mlx->width != width)
	{
		height = data->mlx->height;
		width = data->mlx->width;
		mlx_resize_image(data->canvas, data->mlx->width, data->mlx->height);
		gf_camera_set_res(&data->cam, data->mlx->width, data->mlx->height);
		render(data);
	}
}

int	minirt(char *filename)
{
	t_data		data;

	data.scene = parser(filename);
	if (!data.scene)
		return (1);
	data.mlx = mlx_init(800, 600, "MLX42", true);
	if (!data.mlx)
		return (1);
	data.canvas = mlx_new_image(data.mlx, data.mlx->width, data.mlx->height);
	mlx_image_to_window(data.mlx, data.canvas, 0, 0);

	data.cam = gf_camera_new(data.scene->camera->fov,
		data.scene->camera->origin, data.scene->camera->orientation);
	gf_camera_set_res(&data.cam, data.canvas->width, data.canvas->height);

	mlx_loop_hook(data.mlx, hook, &data);
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
