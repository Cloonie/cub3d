/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:11:33 by mliew             #+#    #+#             */
/*   Updated: 2023/08/03 15:28:56 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if ((dst == src) || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	while (++i < n)
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	return (dst);
}
/*
int	main()
{
	char string[1024];
	int i=0;

	ft_memcpy(string, "12345\000abcde", 11);
	printf("%s\n", string);
	while (i < 11)
	{
		printf("%c", string[i++]);
	}
}
*/