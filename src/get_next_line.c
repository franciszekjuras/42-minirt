/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:34:40 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/28 00:26:47 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

char	*ft_new_save(char *save)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		new[j++] = save[i++];
	new[j] = '\0';
	free(save);
	return (new);
}

char	*ft_get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *save)
{
	char	*buff;
	ssize_t	b;

	buff = (char *)malloc(sizeof(char) * 2);
	if (!buff)
		return (NULL);
	b = 1;
	while (ft_strchrr(save, '\n') == 0 && b != 0)
	{
		b = read(fd, buff, 1);
		if (b == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[b] = '\0';
		save = ft_join(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd, int flag)
{	
	char		*line;
	static char	*save;

	if (flag == 1)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	if (fd < 0)
		return (NULL);
	save = ft_read(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_new_save(save);
	return (line);
}
