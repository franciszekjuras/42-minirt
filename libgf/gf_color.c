/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gf_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:39:22 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/18 09:34:30 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "gf.h"

static int	cap_to_byte(int v)
{
	if (v >= 255.)
		return (255);
	else if (v <= 0.)
		return (0);
	else
		return ((int)(v + 0.5));
}

int	gf_ctoi(t_gf_color color)
{
	return (cap_to_byte(color.r) << 24
		| cap_to_byte(color.g) << 16
		| cap_to_byte(color.b) << 8
		| 255);
}

t_gf_color	gf_rgb(double r, double g, double b)
{
	t_gf_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_gf_color	gf_color_mult(t_gf_color color, double mult)
{
	color.r *= mult;
	color.g *= mult;
	color.b *= mult;
	return (color);
}

t_gf_color	gf_color_channel_mult(t_gf_color color, t_gf_color ch_mult)
{
	color.r *= ch_mult.r;
	color.g *= ch_mult.g;
	color.b *= ch_mult.b;
	return (color);
}
