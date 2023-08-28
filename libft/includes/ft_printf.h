/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:36:35 by mliew             #+#    #+#             */
/*   Updated: 2022/06/24 19:34:03 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

// main ft_printf function
int	ft_printf(const char *str, ...);

// conversions: cspdiuxX%
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int n);
int	ft_puthex(unsigned int n, const char fmt);
int	ft_putpointer(unsigned long n);
int	ft_putunsign(unsigned int n);
int	len_hex(unsigned long n);

#endif