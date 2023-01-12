/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:32:40 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/12 14:54:24 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "input.h"
# include "get_next_line.h"

// parser.c
t_scene	*parser(char *filename);
int		parse_line(t_scene *scene, char **line);

// parser_utils.c
int		splitsize(char **split);
void	free_split(char **split);
void	free_lines(char *line, char **split);
double	ft_atof(const char *nptr);

// parse_objects.c
int		parse_sphere(t_scene *scene, char **line);
int		parse_plane(t_scene *scene, char **line);
int		parse_cylinder(t_scene *scene, char **line);

// parse_lighting.c
int		parse_camera(t_scene *scene, char **line);
int		parse_light(t_scene *scene, char **line);
int		parse_ambient_lighting(t_scene *scene, char **line);

// parse_parameters.c
int		parse_coordinates(t_vec3 *point, char *line);
int		parse_orientation(t_vec3 *point, char *line);
int		parse_color(t_vec3 *color, char *line);

// free_scene.c
void	free_scene(t_scene *scene);

#endif