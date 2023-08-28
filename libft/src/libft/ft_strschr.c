/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strschr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:13:02 by mliew             #+#    #+#             */
/*   Updated: 2023/05/16 16:13:02 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

//	searches for a character in a string and when it reaches the character
//	it null terminates the character and returns the string

char	*ft_strschr(char *s, int c)
{
	int		i;
	char	*new;

	i = 0;
	new = s;
	while (new[i])
	{
		if (new[i] == c)
		{
			new[i] = '\0';
			break ;
		}
		i++;
	}
	return (new);
}
