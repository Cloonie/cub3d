/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:12:43 by mliew             #+#    #+#             */
/*   Updated: 2023/08/03 15:28:56 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// void	ft_putendl_fd(char *s, int fd)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return ;
// 	while (s[i])
// 	{
// 		write (fd, &s[i], 1);
// 		i++;
// 	}
// 	write (fd, "\n", 1);
// }
