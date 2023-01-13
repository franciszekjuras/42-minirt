/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:03:48 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/13 20:29:17 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_UTILS_H
# define FT_GET_NEXT_LINE_UTILS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include <stddef.h>

typedef struct s_lst	t_lst;

struct s_lst
{
	int		id;
	char	*str;
	size_t	size;
	t_lst	*next;
};

size_t	ft_strlen_null(const char *s);
char	*ft_strnsplit(char *str, size_t n);
int		node_appbuf(t_lst *node, const char *buf);

#endif
