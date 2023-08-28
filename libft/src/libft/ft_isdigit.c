/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:11:23 by mliew             #+#    #+#             */
/*   Updated: 2022/05/23 11:11:23 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int main()
{
	printf("%d\n", ft_isdigit('0'));
	printf("%d\n", ft_isdigit('a'));
	printf("%d\n", ft_isdigit('+'));
	printf("%d\n", isdigit('0'));
	printf("%d\n", isdigit('a'));
	printf("%d\n", isdigit('+'));
}
*/