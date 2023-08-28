/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:50:18 by mliew             #+#    #+#             */
/*   Updated: 2023/05/11 15:52:26 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);

int		gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char const *s1, char const *s2);
void	gnl_bzero(void *s, size_t n);
void	*gnl_calloc(size_t count, size_t size);

#endif