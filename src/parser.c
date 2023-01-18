/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:55:10 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/18 16:49:53 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_scene(t_scene *scene)
{
	scene->camera = NULL;
	scene->lights = NULL;
	scene->ambient = NULL;
	scene->objects = NULL;
}

static int	check_file(char *filename)
{
	char	*end;
	int		end_len;
	int		name_len;
	int		i;

	end = ".rt";
	end_len = ft_strlen(end);
	name_len = ft_strlen(filename);
	i = 0;
	while (i < end_len)
	{
		if (filename[name_len - i] != end[end_len - i])
			return (0);
		i++;
	}
	return (1);
}

static int	open_file(char *filename)
{
	int	fd;

	if (!check_file(filename))
	{
		printf("Error : scene file has to end with .rt\n");
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error : couldn't open the file\n");
		exit(1);
	}
	return (fd);
}

int	parse_line(t_scene *scene, char **line)
{
	if (check_line(line))
		printf("Error : input has an unknown character\n");
	else if (!splitsize(line) || !ft_strncmp(line[0], "\n", 2))
		return (0);
	else if (ft_strncmp(line[0], "A", 1) == 0)
		return (parse_ambient_lighting(scene, line));
	else if (ft_strncmp(line[0], "C", 1) == 0)
		return (parse_camera(scene, line));
	else if (ft_strncmp(line[0], "L", 1) == 0)
		return (parse_light(scene, line));
	else if (ft_strncmp(line[0], "sp", 2) == 0)
		return (parse_sphere(scene, line));
	else if (ft_strncmp(line[0], "pl", 2) == 0)
		return (parse_plane(scene, line));
	else if (ft_strncmp(line[0], "cy", 2) == 0)
		return (parse_cylinder(scene, line));
	else if (ft_strncmp(line[0], "pa", 2) == 0)
		return (parse_parabol(scene, line));
	else
		printf("Error : input has an unknown element\n");
	return (1);
}

t_scene	*parser(char *filename)
{
	t_scene	*scene;
	char	**split;
	char	*line;
	int		fd;

	fd = open_file(filename);
	scene = malloc(sizeof(t_scene));
	init_scene(scene);
	line = get_next_line(fd, 0);
	while (line)
	{
		split = ft_split(line, ' ');
		if (parse_line(scene, split))
		{
			free_lines(line, split);
			free_scene(scene);
			get_next_line(fd, 1);
			close(fd);
			return (NULL);
		}
		free_lines(line, split);
		line = get_next_line(fd, 0);
	}
	close(fd);
	return (scene);
}
