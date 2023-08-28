/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:53:40 by mliew             #+#    #+#             */
/*   Updated: 2023/05/11 15:52:14 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	gnl_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

void	*gnl_calloc(size_t count, size_t size)
{
	void	*array;

	if (count >= SIZE_MAX || size >= SIZE_MAX)
		return (0);
	array = malloc(count * size);
	if (!array)
		return (0);
	gnl_bzero(array, count * size);
	return (array);
}

int	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	while (*s && *s != ((char)c))
		s++;
	if (*s == ((char)c))
		return ((char *)s);
	return (0);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*array;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	array = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (array == NULL)
		return (NULL);
	while (*s1)
	{
		array[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		array[i] = *s2;
		i++;
		s2++;
	}
	array[i] = '\0';
	return (array);
}
