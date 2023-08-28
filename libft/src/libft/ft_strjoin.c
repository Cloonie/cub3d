/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:47:43 by mliew             #+#    #+#             */
/*   Updated: 2023/08/03 15:28:56 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*array;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	array = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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
