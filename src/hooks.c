/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:44:25 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/19 22:45:08 by fjuras           ###   ########.fr       */
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

int	handle_key(int keycode, t_gf_ctx *ctx)
{
	if (GF_K_ESC == keycode)
		close_app(ctx);
	return (0);
}
