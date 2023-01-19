/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:38:30 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/19 22:24:47 by fjuras           ###   ########.fr       */
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

static void	parse_integer_params(int *arr, t_ft_argparse *arg, int num)
{
	int		i;
	int		err;
	char	*param;

	i = 0;
	while (i < num && arg->params[i] != NULL)
	{
		param = arg->params[i];
		arr[i] = ft_strtonum(&param, INT_MIN, INT_MAX, &err);
		if (err || *param != '\0')
			break ;
		++i;
	}
	if (i != num)
	{
		ft_dprintf(2,
			"Argument -%c requires %d valid parameters, got only %d\n",
			arg->arg, num, i);
		exit(1);
	}
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
	ctx->w = ft_max(400, ft_min(screen_size[0] * 9 / 10, win_size[0]));
	ctx->h = ft_max(300, ft_min(screen_size[1] * 9 / 10, win_size[1]));
	ctx->win = mlx_new_window(ctx->mlx, ctx->w, ctx->h, "miniRT");
	ctx->img = gf_img(ctx->mlx, ctx->w, ctx->h);
}

static int	close_app(t_gf_ctx *ctx)
{
	mlx_destroy_window(ctx->mlx, ctx->win);
	mlx_destroy_display(ctx->mlx);
	exit(0);
	return (0);
}

static int	handle_key(int keycode, t_gf_ctx *ctx)
{
	if (GF_K_ESC == keycode)
		close_app(ctx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_ft_argparse	*args;
	t_ft_argparse	*arg;

	args = ft_argparse(argc, argv);
	data.ctx.mlx = mlx_init();
	context_init_window(&data.ctx, args);
	arg = ft_argparse_find(args, '-');
	if (arg == NULL || arg->count > 1)
	{
		ft_dprintf(2, "minirt requires one positional argument: <scene> \n");
		return (1);
	}
	data.scene = parser(arg->params[0]);
	ft_argparse_free(args);
	mlx_hook(data.ctx.win, DestroyNotify, 0, &close_app, &data.ctx);
	mlx_hook(data.ctx.win, KeyPress, KeyPressMask, &handle_key, &data.ctx);
	if (data.scene == NULL)
		return (1);
	data.cam = gf_camera_new(data.scene->camera->fov,
			data.scene->camera->origin, data.scene->camera->orientation);
	gf_camera_set_res(&data.cam, data.ctx.w, data.ctx.h);
	render(&data);
	mlx_loop(data.ctx.mlx);
}
