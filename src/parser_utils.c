/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:45:43 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/12 14:08:43 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static double	return_decimal(const char *nptr, int i)
{
	double	sum;
	double	devider;

	if (nptr[i] != '.')
		return (0);
	i++;
	sum = 0;
	devider = 10;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum = sum + ((nptr[i] - '0') / devider);
		devider = devider * 10;
		i++;
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
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			negative = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum = sum * 10 + (nptr[i] - '0');
		i++;
	}
	sum = sum + return_decimal(nptr, i);
	sum = sum * negative;
	return (sum);
}
