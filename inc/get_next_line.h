/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:29:00 by jkarosas          #+#    #+#             */
/*   Updated: 2023/01/12 13:41:52 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "../libft/libft.h"

char	*get_next_line(int fd, int flag);

char	*ft_read(int fd, char *save);

char	*ft_get_line(char *save);

char	*ft_new_save(char *save);

char	*ft_join(char *s1, char *s2);

char	*ft_strchrr(char *save, int c);

#endif