/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:44:25 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/20 14:56:47 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <libgf/gf_keys.h>

int	close_app(t_gf_ctx *ctx)
{
	mlx_destroy_window(ctx->mlx, ctx->win);
	mlx_destroy_display(ctx->mlx);
	exit(0);
	return (0);
}

int	on_resize(t_data *data)
{
	render(data);
	return (0);
}

int	handle_key(int keycode, t_gf_ctx *ctx)
{
	if (GF_K_ESC == keycode)
		close_app(ctx);
	return (0);
}
