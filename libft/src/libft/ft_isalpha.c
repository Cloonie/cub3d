/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:11:10 by mliew             #+#    #+#             */
/*   Updated: 2022/05/23 11:11:10 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/*
#include <stdio.h>
#include <ctype.h>

int main()
{
	printf("%d\n", ft_isalpha('A'));
	printf("%d\n", ft_isalpha('a'));
	printf("%d\n", ft_isalpha('+'));
	printf("%d\n", isalpha('A'));
	printf("%d\n", isalpha('a'));
	printf("%d\n", isalpha('+'));
}
*/