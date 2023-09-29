/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:59:28 by mliew             #+#    #+#             */
/*   Updated: 2023/09/11 18:59:28 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	quit(t_vars *vars, char *msg)
{
	int	i;

	i = -1;
	if (vars->mapdata.map)
	{
		while (vars->mapdata.map[++i])
			free(vars->mapdata.map[i]);
		free(vars->mapdata.map);
	}
	printf("Error\n");
	perror(msg);
	system("leaks cub3d");
	exit(1);
}

int	window_close(t_vars *vars)
{
	quit(vars, "Window closed: close window button.\n");
	return (0);
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_miniplayer(t_vars *vars, int size)
{
	t_pixel	player;
	float	tmp_x;
	float	tmp_y;

	tmp_x = ((vars->px - (MAP_S / 2)) / MAP_S) * size + (size / 2);
	tmp_y = ((vars->py - (MAP_S / 2)) / MAP_S) * size + (size / 2);
	player.x = tmp_x - (size / 10);
	player.y = tmp_y - (size / 10);
	player.addr = mlx_get_data_addr(vars->img, &player.bits_per_pixel,
			&player.size_line, &player.endian);
	while (player.y < (tmp_y + (size / 10)))
	{
		while (player.x < (tmp_x + (size / 10)))
		{
			draw_pixel(vars, player.x, player.y, 0x00FF00);
			player.x++;
		}
		player.x = tmp_x - (size / 10);
		player.y++;
	}
}

void	draw_minimap(t_vars *vars, int size)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < (vars->mapdata.y * size))
	{
		while (++x < (vars->mapdata.x * size))
		{
			if (y % size == 0 || x % size == 0)
				draw_pixel(vars, x, y, 0x0F0F0F);
			else if (vars->mapdata.map[y / size][x / size] == '1')
				draw_pixel(vars, x, y, 0xFFFFFF);
			else if (vars->mapdata.map[y / size][x / size] == '2')
				draw_pixel(vars, x, y, 0xFFFF00);
			else if (vars->mapdata.map[y / size][x / size] == '3')
				draw_pixel(vars, x, y, 0xFFFF00);
			else
				draw_pixel(vars, x, y, 0x999999);
		}
		x = -1;
	}
}
