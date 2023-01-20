/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:38:30 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/20 16:12:54 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <mlx/mlx.h>
#include <X11/X.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include <libgf/gf_keys.h>
#include "minirt.h"
#include "parser.h"

static int	check_scene(t_scene *scene)
{
	if (!scene->camera)
	{
		printf("Error : undefined camera\n");
		free_scene(scene);
		return (1);
	}
	if (!scene->ambient)
	{
		printf("Error : undefined ambient lighting\n");
		free_scene(scene);
		return (1);
	}
	if (!scene->lights)
	{
		printf("Error : undefined lights\n");
		free_scene(scene);
		return (1);
	}
	return (0);
}

static void	context_init_window(t_gf_ctx *ctx, t_ft_argparse *args)
{
	t_ft_argparse	*arg;
	int				win_size[2];
	int				screen_size[2];

	arg = ft_argparse_find(args, 's');
	if (arg)
		parse_integer_params(win_size, arg, 2);
	else
	{
		win_size[0] = 800;
		win_size[1] = 600;
	}
	mlx_get_screen_size(ctx->mlx, &screen_size[0], &screen_size[1]);
	ctx->w = ft_max(300, ft_min(screen_size[0] * 9 / 10, win_size[0]));
	ctx->h = ft_max(200, ft_min(screen_size[1] * 9 / 10, win_size[1]));
	ctx->win = mlx_new_window(ctx->mlx, ctx->w, ctx->h, "miniRT");
	ctx->img = gf_img(ctx->mlx, ctx->w, ctx->h);
}

static void	setup_hooks(t_data *data)
{
	mlx_do_key_autorepeatoff(data->ctx.mlx);
	mlx_hook(data->ctx.win, DestroyNotify, 0, &close_app, data);
	mlx_key_hook(data->ctx.win, &handle_key, data);
	mlx_hook(data->ctx.win,
		ConfigureNotify, StructureNotifyMask, &on_resize, &data->ctx);
}

static int	cleanup_err(t_ft_argparse	*args, const char *msg)
{
	ft_argparse_free(args);
	if (msg != NULL)
		printf(2, "%s\n", msg);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_ft_argparse	*args;
	t_ft_argparse	*arg;

	args = ft_argparse(argc, argv);
	arg = ft_argparse_find(args, '-');
	if (arg == NULL || arg->count > 1)
		return (cleanup_err(args, "Error: no required argument: <scene>"));
	data.scene = parser(arg->params[0]);
	if (data.scene == NULL || check_scene(data.scene))
		return (cleanup_err(args, NULL));
	data.ctx.mlx = mlx_init();
	context_init_window(&data.ctx, args);
	ft_argparse_free(args);
	data.cam = gf_camera_new(data.scene->camera->fov,
			data.scene->camera->origin, data.scene->camera->orientation);
	gf_camera_set_res(&data.cam, data.ctx.w, data.ctx.h);
	render(&data);
	setup_hooks(&data);
	mlx_loop(data.ctx.mlx);
}
