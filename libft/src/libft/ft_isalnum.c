/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:11:03 by mliew             #+#    #+#             */
/*   Updated: 2022/05/23 11:11:03 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int main()
{
	int test;

	test = 'A';
	printf("%d\n", ft_isalnum(test));
	printf("%d\n", isalnum(test));
}
*/