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

void	print_img(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx, screenWidth, screenHeight);

	t_pixel bg;
	bg.addr = mlx_get_data_addr(vars->img, &bg.bits_per_pixel, &bg.size_line, &bg.endian);
	int bgx = 0;
	int bgy = 0;
	while (bgy < 720)
	{
		while (bgx < 720)
		{
			int pixel = bgy * bg.size_line + bgx * (bg.bits_per_pixel / 8);
			if (worldMap[bgx/30][bgy/30] == 1)
			{
				bg.addr[pixel] = 0xFF;		// Blue
				bg.addr[pixel + 1] = 0xFF;	// Green
				bg.addr[pixel + 2] = 0xFF;	// Red
				bg.addr[pixel + 3] = 0x00;	// Alpha
			}
			else if (worldMap[bgx/30][bgy/30] == 2)
				bg.addr[pixel] = 0xFF;		// Blue
			else if (worldMap[bgx/30][bgy/30] == 3)
				bg.addr[pixel + 2] = 0xFF;	// Red
			else if (worldMap[bgx/30][bgy/30] == 4)
			{
				bg.addr[pixel] = 0xFF;		// Blue
				bg.addr[pixel + 2] = 0xFF;	// Red
			}
			bgx++;
		}
		bgx = 0;
		bgy++;
	}

	t_pixel player;
	player.addr = mlx_get_data_addr(vars->img, &player.bits_per_pixel, &player.size_line, &player.endian);
	int px = vars->pos_x;
	int py = vars->pos_y;
	while (py < (vars->pos_y + vars->pos_size))
	{
		while (px < (vars->pos_x + vars->pos_size))
		{
			int pixel = py * player.size_line + px * (player.bits_per_pixel / 8);
			// player.addr[pixel] = 0x00;		// Blue
			player.addr[pixel + 1] = 0xFF;	// Green
			// player.addr[pixel + 2] = 0x00;	// Red
			// player.addr[pixel + 3] = 0x00;	// Alpha
			px++;
		}
		px = vars->pos_x;
		py++;
	}

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);

	// while (++vars->map_y * vars->map_size < screenHeight)
	// {
	// 	while (++vars->map_x * vars->map_size < screenWidth)
	// 	{
	// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->bg_img,
	// 			vars->map_x * vars->map_size, vars->map_y * vars->map_size);
	// 	}
	// 	vars->map_x = -1;
	// }
	// vars->map_y = -1;
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->pos_img,
	// 	vars->pos_x, vars->pos_y);
}

int	loop_hook(int keycode, t_vars *vars)
{
	(void)keycode;
	(void)vars;
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	// printf("key_hook func keycode: %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == W)
		vars->pos_y -= 6;
	if (keycode == A)
		vars->pos_x -= 6;
	if (keycode == S)
		vars->pos_y += 6;
	if (keycode == D)
		vars->pos_x += 6;
	print_img(vars);
	return (0);
}

void	init(t_vars	*vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, screenWidth, screenHeight, "Raycaster");
	vars->map_x = -1;
	vars->map_y = -1;
	vars->map_size = 24;
	vars->chunk_size = 24;
	vars->pos_size = 12;
	vars->pos_x = 300;
	vars->pos_y = 240;
}

int	main(void)
{
	t_vars	vars;

	init(&vars);
	print_img(&vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}
