/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:10:27 by mliew             #+#    #+#             */
/*   Updated: 2022/05/23 11:10:27 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] == '-')
		neg *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = (nbr * 10) + (str[i++] - '0');
	return (nbr * neg);
}

/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf(":%d:\n", ft_atoi(" -123 45"));
    printf(":%d:\n", atoi(" -123 45"));
}
*/