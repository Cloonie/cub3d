/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:03:43 by mliew             #+#    #+#             */
/*   Updated: 2023/08/03 15:28:56 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_numlen(long n)
{
	int	ft_numlen;

	ft_numlen = 0;
	if (n == '\0')
		return (1);
	if (n < 0)
	{
		n *= -1;
		ft_numlen++;
	}
	while (n > 0)
	{
		n /= 10;
		ft_numlen++;
	}
	return (ft_numlen);
}

static char	*checknb(long nb, char *str, long i)
{
	if (nb == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[i] = 48 + (nb % 10);
		nb /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = n;
	i = ft_numlen(n);
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	str[i--] = '\0';
	return (checknb(nb, str, i));
}
