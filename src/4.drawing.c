/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.drawing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:23:59 by mliew             #+#    #+#             */
/*   Updated: 2023/09/11 15:23:59 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	After using mlx_get_data_addr to get the return value of an image address
	use this formula:
	pos = y * size_line + x * (bits_per_pixel / 8);
	to get the position of that pixel using the address then apply
	colours or a pixel colour from another address from an xpm file.

	color uses ARGB format: 0xFF005599
	each two characters after 0x represents Alpha, Red, Green, Blue

	Example:
	addr[pos] = 0x00;		Blue
	addr[pos + 1] = 0x55;	Green
	addr[pos + 2] = 0x99;	Red
	addr[pos + 3] = 0xFF;	Alpha / Transparency
*/
void	set_colour(t_pixel *pixel, int color)
{
	pixel->alpha = (color >> 24) & 0xFF;
	pixel->red = (color >> 16) & 0xFF;
	pixel->green = (color >> 8) & 0xFF;
	pixel->blue = color & 0xFF;

	pixel->pos = pixel->y * pixel->size_line + pixel->x
		* (pixel->bits_per_pixel / 8);
	pixel->addr[pixel->pos] = pixel->blue;
	pixel->addr[pixel->pos + 1] = pixel->green;
	pixel->addr[pixel->pos + 2] = pixel->red;
	pixel->addr[pixel->pos + 3] = pixel->alpha;
}

/*
	Takes the current coordinates of the player and prints a square around it.
*/
void	draw_player(t_vars *vars)
{
	t_pixel	player;

	player.x = vars->px - (vars->player_size / 2);
	player.y = vars->py - (vars->player_size / 2);
	player.addr = mlx_get_data_addr(vars->img, &player.bits_per_pixel,
			&player.size_line, &player.endian);
	while (player.y < (vars->py + (vars->player_size / 2)))
	{
		while (player.x < (vars->px + (vars->player_size / 2)))
		{
			set_colour(&player, 0xFF00FF00);
			player.x++;
		}
		player.x = vars->px - (vars->player_size / 2);
		player.y++;
	}
}

/*
	Current background is printed each pixel from left to right by each row
*/
void	draw_bg(t_vars *vars)
{
	t_pixel	bg;

	bg.addr = mlx_get_data_addr(vars->img, &bg.bits_per_pixel,
			&bg.size_line, &bg.endian);
	bg.x = -1;
	bg.y = -1;
	while (++bg.y < (mapY * mapS))
	{
		while (++bg.x < (mapX * mapS))
		{
			if (bg.y % mapS == 0 || bg.x % mapS == 0)
				set_colour(&bg, 0xFF999999);
			else if (map[bg.y / mapS][bg.x / mapS] == 1)
				set_colour(&bg, 0xFFFFFFFF);
			else
				set_colour(&bg, 0xFF505050);
		}
		bg.x = -1;
	}
}

/*
	Variable initialization for Bresenham's line algorithm for draw_line function

	x0 and y0:	x and y coordinates of the starting point of the line.

	x1 and y1:	x and y coordinates of the ending point of the line.

	color:		integer representing the color of the line.

	dx and dy:	absolute differences between the coordinates
				the length and direction of the line.

	sx and sy:	sign (+ or -) of the x y direction in which the line is drawn.
				They are used to control the step size in each direction.

	err:		the decision parameter used in the Bresenham algorithm.
				helps determine which pixel to plot in each step of the
				line drawing process. It is initially set to dx - dy.

	err2:		This variable stores twice the value of the err variable and
				is used in calculations to decide whether to increment the
				x or y coordinate in each step.

	curr x/y:	the current position of the pixel being drawn.
				updated in each iteration of the loop to plot the line pixel by pixel.
*/
t_line	set_line(int x0, int y0, int x1, int y1)
{
	t_line	line;

	line.x0 = x0;
	line.y0 = y0;
	line.x1 = x1;
	line.y1 = y1;
	line.curr_x = x0;
	line.curr_y = y0;
	line.dx = abs(x1 - x0);
	line.dy = abs(y1 - y0);
	line.err = line.dx - line.dy;
	if (x0 < x1)
		line.sx = 1;
	else
		line.sx = -1;
	if (y0 < y1)
		line.sy = 1;
	else
		line.sy = -1;
	return (line);
}

/*
	Bresenham's line algorithm:

	efficiently determines which pixels to plot to approximate a straight line
	between two points on a grid,
	taking into account the step size and decision parameter.
	It is widely used in computer graphics due to its simplicity and efficiency.
*/
void	draw_line(t_vars *vars, t_line *line, int colour)
{
	while (1)
	{
		mlx_pixel_put(vars->mlx, vars->win, line->curr_x, line->curr_y, colour);
		if (line->curr_x == line->x1 && line->curr_y == line->y1)
			break ;
		line->err2 = 2 * line->err;
		if (line->err2 > -line->dy)
		{
			line->err -= line->dy;
			line->curr_x += line->sx;
		}
		if (line->err2 < line->dx)
		{
			line->err += line->dx;
			line->curr_y += line->sy;
		}
	}
}
