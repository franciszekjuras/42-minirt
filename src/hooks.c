/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:44:25 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/20 15:57:16 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
