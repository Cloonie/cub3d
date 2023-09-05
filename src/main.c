/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:33:43 by mliew             #+#    #+#             */
/*   Updated: 2023/08/28 14:33:43 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	After using mlx_get_data_addr to get the return value of an image address
	use this formula [pos = y * size_line + x * (bits_per_pixel / 8)] to get
	the position of that pixel using the address then apply colours or a pixel
	colour from another address from an xpm file.

	addr[pos] = 0x00;		Blue
	addr[pos + 1] = 0xFF;	Green
	addr[pos + 2] = 0x50;	Red
	addr[pos + 3] = 0x00;	Alpha
*/

void	draw_player(t_vars *vars)
{
	t_pixel	player;

	player.x = vars->px;
	player.y = vars->py;

	player.addr = mlx_get_data_addr(vars->img, &player.bits_per_pixel, &player.size_line, &player.endian);
	while (player.y < (vars->py + vars->player_size))
	{
		while (player.x < (vars->px + vars->player_size))
		{
			player.pos = player.y * player.size_line + player.x * (player.bits_per_pixel / 8);
			player.addr[player.pos] = 0x00;		// Blue
			player.addr[player.pos + 1] = 0xFF;	// Green
			player.addr[player.pos + 2] = 0x00;	// Red
			player.addr[player.pos + 3] = 0x00;	// Alpha
			player.x++;
		}
		player.x = vars->px;
		player.y++;
	}
}

void	draw_bg(t_vars *vars)
{
	t_pixel	bg;

	bg.addr = mlx_get_data_addr(vars->img, &bg.bits_per_pixel, &bg.size_line, &bg.endian);
	bg.x = -1;
	bg.y = -1;
	while (++bg.y < (mapHeight * chunkSize))
	{
		while (++bg.x < (mapWidth * chunkSize))
		{
			int pixel = bg.y * bg.size_line + bg.x * (bg.bits_per_pixel / 8);
			int x = bg.x/chunkSize;
			int y = bg.y/chunkSize;
			if (bg.y % chunkSize == 0 || bg.x % chunkSize == 0)
				;
			else if (worldMap[y][x] == 1)
			{
				bg.addr[pixel] = 0xFF;		// Blue
				bg.addr[pixel + 1] = 0xFF;	// Green
				bg.addr[pixel + 2] = 0xFF;	// Red
			}
			else if (worldMap[y][x] == 2)
			{
				bg.addr[pixel] = 0xFF;		// Blue
				bg.addr[pixel + 1] = 0x00;	// Green
				bg.addr[pixel + 2] = 0x00;	// Red
			}
			else if (worldMap[y][x] == 3)
			{
				bg.addr[pixel] = 0x00;		// Blue
				bg.addr[pixel + 1] = 0x00;	// Green
				bg.addr[pixel + 2] = 0xFF;	// Red
			}
			else
			{
				bg.addr[pixel] = 0x50;		// Blue
				bg.addr[pixel + 1] = 0x50;	// Green
				bg.addr[pixel + 2] = 0x50;	// Red
			}
		}
		bg.x = -1;
	}
}

void	draw_line(t_vars *vars)
{
	t_pixel	line;

	line.x = vars->px + 5;
	line.y = vars->py + 5;
	for(int i = 0; i < 10; i++)
	{
		mlx_pixel_put(vars->mlx, vars->win, line.x, line.y, 0xFFFF00);
		line.x += vars->pdx;
		line.y += vars->pdy;
	}
}

void	print_img(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx, screenWidth, screenHeight);
	draw_bg(vars);
	draw_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	draw_line(vars);
	mlx_destroy_image(vars->mlx, vars->img);
}

// int	loop_hook(int keycode, t_vars *vars)
// {
// 	(void)keycode;
// 	(void)vars;
// 	return (0);
// }

int	key_hook(int keycode, t_vars *vars)
{
	int	move = 5;
	// printf("key_hook func keycode: %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == A)
	{
		vars->pa -= 0.1;
		if (vars->pa < 0)
			vars->pa += 2 * PI;
		vars->pdx = cos(vars->pa) * 10;
		vars->pdy = sin(vars->pa) * 10;
	}
	if (keycode == D)
	{
		vars->pa += 0.1;
		if (vars->pa > 2 * PI)
			vars->pa -= 2 * PI;
		vars->pdx = cos(vars->pa) * 10;
		vars->pdy = sin(vars->pa) * 10;
	}
	if (keycode == W)
	{
		vars->px += vars->pdx;
		vars->py += vars->pdy;
	}
	if (keycode == S)
	{
		vars->px -= vars->pdx;
		vars->py -= vars->pdy;
	}
	print_img(vars);
	printf("player x:%f y:%f\n", vars->px, vars->py);
	return (0);
}

void	init(t_vars	*vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, screenWidth, screenHeight, "Raycaster");
	vars->player_size = 10;
	vars->px = 100;
	vars->py = 100;
	vars->pdx = cos(vars->pa);
	vars->pdy = sin(vars->pa);
	vars->pa = 0;
}

int	main(void)
{
	t_vars	vars;

	init(&vars);
	print_img(&vars);
	// mlx_loop_hook(vars.mlx, loop_hook, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}
