/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:15:56 by mliew             #+#    #+#             */
/*   Updated: 2023/08/03 15:28:56 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	res;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	res = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize > len_dst)
		res = len_dst + len_src;
	else
		res = len_src + dstsize;
	while (src[i] && ((len_dst + 1) < dstsize))
	{
		dst[len_dst] = src[i];
		len_dst++;
		i++;
	}
	dst[len_dst] = '\0';
	return (res);
}
