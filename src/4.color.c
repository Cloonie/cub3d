/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:25:03 by mliew             #+#    #+#             */
/*   Updated: 2023/09/19 14:25:03 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Takes in a hex_color in the format 0xRRGGBB values between
	00-FF for each RR/GG/BB and converts into 3 values of 0-255

	*alpha = (color >> 24) & 0xFF;
	*red = (color >> 16) & 0xFF;
	*green = (color >> 8) & 0xFF;
	*blue = color & 0xFF;
*/
void	hex_to_rgb(int hex_color, int *red, int *green, int *blue)
{
	*red = (hex_color >> 16) & 0xFF;
	*green = (hex_color >> 8) & 0xFF;
	*blue = hex_color & 0xFF;
}

/*
	Takes in a red green blue in the format int 0 - 255
	and converts it to one format 0xFFFFFF
*/
int	rgb_to_hex(int red, int green, int blue)
{
	return (((int)red << 16)
		| ((int)green << 8)
		| (int)blue);
}
