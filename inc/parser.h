/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:32:40 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/27 16:12:07 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "input.h"
# include "get_next_line.h"
# include <libft/libft.h>

typedef struct s_parse_data
{
	t_scene	*scene;
	char	**split;
	char	*line;
	int		fd;
}	t_parse_data;

// parser.c
t_scene	*parser(char *filename);
int		parse_line(t_scene *scene, char **line);

// parser_utils.c
int		splitsize(char **split);
void	free_split(char **split);
void	free_lines(char *line, char **split);
double	ft_atof(const char *nptr);
int		check_line(char **split);
int		cleanup_split(char **split, const char *msg);
int		cleanup(const char *msg);
int		is_atof_abs_just_gt_1(char *nb);

// parse_objects.c
int		parse_sphere(t_scene *scene, char **line);
int		parse_plane(t_scene *scene, char **line);
int		parse_cylinder(t_scene *scene, char **line);
int		parse_parabol(t_scene *scene, char **line);

// parse_lighting.c
int		parse_camera(t_scene *scene, char **line);
int		parse_light(t_scene *scene, char **line);
int		parse_ambient_lighting(t_scene *scene, char **line);

// parse_parameters.c
int		parse_coordinates(t_v3 *point, char *line);
int		parse_orientation(t_v3 *point, char *line);
int		parse_color(t_gf_color *color, char *line);

// free_scene.c
void	free_scene(t_scene *scene);

#endif