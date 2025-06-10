/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:49:26 by arimoham          #+#    #+#             */
/*   Updated: 2025/04/27 12:25:03 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_gnl_strlen(char const *str);
char	*ft_gnl_strdup(char const *src);
char	*save_after_nl(char *curr_buffer);
char	*save_new_line(char *curr_buffer);
char	*read_buffer_line(char *curr_buffer, int fd);
char	*ft_gnl_strchr(char const *str, int character);
char	*ft_gnl_strjoin(char const *s1, char const *s2);
char	*read_buffer(char *curr_buff, char *tmp_buffer, int fd, ssize_t *byte);

#endif