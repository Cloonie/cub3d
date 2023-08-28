/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:11:37 by mliew             #+#    #+#             */
/*   Updated: 2023/08/03 15:28:56 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (!dst && !src)
		return (NULL);
	if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

// int main()
// {
// 	char	dest[] = "HelloWorld		";
// 	char	sour[] = "1234567890";
// 	int i = 0;

// 	printf("Before: %s\n", dest);
// 	ft_memmove(dest, sour, 10);
// 	printf("After : %s\n", dest);
// }
// src   2 x 3 y 4 z 5 w 6 v
// dst				  5 h 6 e 7 l 8 l 9 o
