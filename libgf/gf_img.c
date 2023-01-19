/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gf_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:40:47 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/19 21:43:08 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx/mlx.h>
#include <libft/libft.h>
#include "gf.h"

void	gf_img_pxput(t_gf_img *img, int x, int y, int color)
{
	int	*adr;

	adr = img->adr + img->lnlen * y;
	adr += x;
	*adr = color;
}

t_gf_img	gf_img(void *mlx, int w, int h)
{
	t_gf_img	img;
	int			bitspp;

	img.img = mlx_new_image(mlx, w, h);
	img.w = w;
	img.h = h;
	img.adr = mlx_get_data_addr(img.img, &bitspp, &img.lnlen, &img.endn);
	img.bypp = bitspp / 8;
	if (img.bypp != 4)
	{
		ft_dprintf(2, "Error: Unsupported pixel width %d\n", img.bypp);
		exit(1);
	}
	return (img);
}

void	gf_img_put(t_gf_ctx *ctx, t_gf_img *img)
{
	mlx_put_image_to_window(ctx->mlx, ctx->win, img->img,
		0, 0);
}

void	gf_img_clear(t_gf_img *img)
{	
	ft_bzero(img->adr, img->lnlen * img->h);
}
