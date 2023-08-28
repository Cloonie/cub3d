/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:14:18 by mliew             #+#    #+#             */
/*   Updated: 2022/06/24 18:23:05 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len_num(long n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	ft_putunsign(unsigned int n)
{
	int	zero;

	zero = 0;
	if (n == 0)
		zero = 1;
	if (n > 9)
		ft_putunsign(n / 10);
	ft_putchar(n % 10 + '0');
	return (len_num(n) + zero);
}

// int	main(void)
// {
// 	printf("%u\n", 2147483647);
// 	ft_putunsign(2147483647);
// }