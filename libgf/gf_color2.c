/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gf_color2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:39:22 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/18 12:23:39 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "gf.h"

void	gf_color_iadd(t_gf_color *color, t_gf_color add)
{
	color->r += add.r;
	color->g += add.g;
	color->b += add.b;
}

t_gf_color	gf_color_mult(t_gf_color color, double mult)
{
	color.r *= mult;
	color.g *= mult;
	color.b *= mult;
	return (color);
}

t_gf_color	gf_color_ch_mult(t_gf_color color, t_gf_color ch, double mult)
{
	color.r *= ch.r * mult / 255.;
	color.g *= ch.g * mult / 255.;
	color.b *= ch.b * mult / 255.;
	return (color);
}
