/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:28:56 by mliew             #+#    #+#             */
/*   Updated: 2022/06/24 19:39:19 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int n, const char fmt)
{
	if (n >= 16)
	{
		ft_puthex(n / 16, fmt);
		ft_puthex(n % 16, fmt);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
		{
			if (fmt == 'x')
				ft_putchar(n - 10 + 'a');
			if (fmt == 'X')
				ft_putchar(n - 10 + 'A');
		}
	}
	return (len_hex(n));
}

// int	main(int ac, char **av)
// {
// 	int hex = atoi(av[1]);

// 	if (ac == 2)
// 	{
// 		ft_puthex(hex);
// 		printf("\n%x\n", hex);
// 	}
// 	else
// 		return (0);
// }