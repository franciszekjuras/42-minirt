/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:01:34 by fjuras            #+#    #+#             */
/*   Updated: 2023/01/13 20:30:07 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_get_next_line_utils.h"

static t_lst	*gnl_root(void)
{
	static t_lst	root = {0, 0, 0, 0};

	return (&root);
}

/**
 * @brief Check for buffered data from file descriptor `fd`.
 * Return appropriate lst node (creating it if necessary)
 * and set value addressed by `i_p` to the first newline in the buffer
 * or its end. 
 * @param root root of a lst
 * @param fd file descriptor
 * @param i_p pointer for storing position of newline or end of buffer
 * @return t_lst* pointer to node corresponding to `fd`
 */
static t_lst	*process_buffered(int fd, size_t *i_p)
{
	t_lst	*node;
	size_t	i;

	node = gnl_root()->next;
	while (node != 0 && node->id != fd)
		node = node->next;
	i = 0;
	if (node == 0)
	{
		node = malloc(sizeof(t_lst));
		if (node == 0)
			return (0);
		node->id = fd;
		node->str = 0;
		node->size = 0;
		node->next = gnl_root()->next;
		gnl_root()->next = node;
	}
	else if (node->str != 0)
		while (node->str[i] != '\0' && node->str[i] != '\n')
			i++;
	*i_p = i;
	return (node);
}

void	*gnl_close(int fd)
{
	t_lst	*next;
	t_lst	*prev;

	prev = gnl_root();
	while (prev->next != 0 && prev->next->id != fd)
		prev = prev->next;
	next = prev->next;
	prev->next = next->next;
	free(next->str);
	free(next);
	return (0);
}

/**
 * @brief Split, allocate and return line from `node->str`.
 * If end of file was reached, remove node and return null. 
 * @param root root of a lst
 * @param node node in a lst
 * @param i position of end of lint
 * @return char* allocated line
 */
static char	*parse_line(t_lst *node, size_t i)
{
	char	*line;

	if (node->str[i] != '\0')
		i++;
	if (i == 0)
		return (gnl_close(node->id));
	line = ft_strnsplit(node->str, i);
	if (line == 0)
		return (gnl_close(node->id));
	return (line);
}

char	*ft_get_next_line(int fd)
{
	t_lst			*node;
	char			*buf;
	ssize_t			char_read;
	size_t			i;

	if (gnl_root()->str == 0 && BUFFER_SIZE > 0)
		gnl_root()->str = malloc(BUFFER_SIZE + 1);
	buf = gnl_root()->str;
	node = process_buffered(fd, &i);
	if (node == 0 || buf == 0)
		return (0);
	char_read = -1;
	while ((node->str == 0 || node->str[i] != '\n') && char_read != 0)
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
			return (gnl_close(fd));
		buf[char_read] = '\0';
		if (!node_appbuf(node, buf))
			return (gnl_close(fd));
		while (node->str[i] != '\0' && node->str[i] != '\n')
			i++;
	}
	return (parse_line(node, i));
}
