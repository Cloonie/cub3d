/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:36:47 by mliew             #+#    #+#             */
/*   Updated: 2023/08/03 15:28:56 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// The strchr() function locates the first occurrence of c 
// (converted to a char) in the string pointed to by s.
// The terminating null character is considered to be part of the string;
// therefore if c is `\0', the functions locate the terminating `\0'.

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != ((char)c))
		s++;
	if (*s == ((char)c))
		return ((char *)s);
	return (0);
}
