/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:06:01 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/27 16:12:02 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	compare(char c)
{
	if (ft_isdigit(c) || c == '.' || c == ',' || c == '-' || c == '\n')
		return (0);
	return (1);
}

int	check_line(char **split)
{
	int	i;
	int	y;

	if (split[0] == NULL)
		return (0);
	i = 1;
	while (split[i])
	{
		y = 0;
		while (split[i][y])
		{
			if (compare(split[i][y]))
				return (1);
			y++;
		}
		i++;
	}
	return (0);
}

int	cleanup(const char *msg)
{
	if (msg != NULL)
		printf("%s\n", msg);
	return (1);
}

int	cleanup_split(char **split, const char *msg)
{
	free_split(split);
	if (msg != NULL)
		printf("%s\n", msg);
	return (1);
}

int	is_atof_abs_just_gt_1(char *nb)
{
	char	*zeros;

	if (ft_strncmp(nb, "1.", 2) == 0)
		zeros = &nb[2];
	else if (ft_strncmp(nb, "-1.", 3) == 0)
		zeros = &nb[3];
	else
		return (0);
	while (*zeros == '0')
		++zeros;
	if (*zeros != '\0')
		return (1);
	return (0);
}
