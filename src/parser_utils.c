/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:45:43 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/27 16:26:32 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parser.h"

int	splitsize(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_lines(char *line, char **split)
{
	free(line);
	free_split(split);
}

static double	return_decimal(const char *nptr, int *i)
{
	double	sum;
	double	devider;

	if (nptr[*i] != '.')
		return (0);
	++(*i);
	sum = 0;
	devider = 10;
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		sum = sum + ((nptr[*i] - '0') / devider);
		devider = devider * 10;
		++(*i);
	}
	return (sum);
}

double	ft_atof(const char *nptr)
{
	double	sum;
	double	negative;
	int		i;

	sum = 0;
	negative = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		negative = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		++i;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum = sum * 10 + (nptr[i] - '0');
		i++;
	}
	sum = sum + return_decimal(nptr, &i);
	sum = sum * negative;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] != '\0')
		return (NAN);
	return (sum);
}
