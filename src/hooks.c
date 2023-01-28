/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:44:25 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/28 18:59:37 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "minirt.h"
#include "parser.h"
#include <libgf/gf_keys.h>

int	close_app(t_data *data)
{
	mlx_destroy_image(data->ctx.mlx, data->ctx.img.img);
	mlx_destroy_window(data->ctx.mlx, data->ctx.win);
	mlx_destroy_display(data->ctx.mlx);
	free_scene(data->scene);
	free(data->ctx.mlx);
	exit(0);
	return (0);
}

int	on_resize(t_gf_ctx *ctx)
{
	gf_img_put(ctx, &ctx->img);
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	if (GF_K_ESC == keycode)
		close_app(data);
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_do_key_autorepeatoff(data->ctx.mlx);
	mlx_hook(data->ctx.win, DestroyNotify, 0, &close_app, data);
	mlx_key_hook(data->ctx.win, &handle_key, data);
	mlx_hook(data->ctx.win,
		ConfigureNotify, StructureNotifyMask, &on_resize, &data->ctx);
}
