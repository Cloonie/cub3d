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

void	print_player(t_vars *vars)
{
	t_pixel player;
	player.x = vars->pos_x;
	player.y = vars->pos_y;

	player.addr = mlx_get_data_addr(vars->img, &player.bits_per_pixel, &player.size_line, &player.endian);
	while (player.y < (vars->pos_y + vars->player_size))
	{
		while (player.x < (vars->pos_x + vars->player_size))
		{
			player.pos = player.y * player.size_line + player.x * (player.bits_per_pixel / 8);
			// player.addr[player.pos] = 0x00;		// Blue
			player.addr[player.pos + 1] = 0xFF;	// Green
			// player.addr[player.pos + 2] = 0x00;	// Red
			// player.addr[player.pos + 3] = 0x00;	// Alpha
			player.x++;
		}
		player.x = vars->pos_x;
		player.y++;
	}
}

void	print_img(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx, screenWidth, screenHeight);

	t_pixel bg;
	bg.addr = mlx_get_data_addr(vars->img, &bg.bits_per_pixel, &bg.size_line, &bg.endian);
	bg.x = -1;
	bg.y = -1;
	while (++bg.y < (mapHeight * chunkSize))
	{
		while (++bg.x < (mapWidth * chunkSize))
		{
			int pixel = bg.y * bg.size_line + bg.x * (bg.bits_per_pixel / 8);
			if (worldMap[bg.y/chunkSize][bg.x/chunkSize] == 1)
			{
				bg.addr[pixel] = 0xFF;		// Blue
				bg.addr[pixel + 1] = 0xFF;	// Green
				bg.addr[pixel + 2] = 0xFF;	// Red
			}
			else if (worldMap[bg.y/chunkSize][bg.x/chunkSize] == 2)
				bg.addr[pixel] = 0xFF;		// Blue
			else if (worldMap[bg.y/chunkSize][bg.x/chunkSize] == 3)
				bg.addr[pixel + 2] = 0xFF;	// Red
			// else
			// {
			// 	bg.addr[pixel] = 0x50;		// Blue
			// 	bg.addr[pixel + 1] = 0x50;	// Green
			// 	bg.addr[pixel + 2] = 0x50;	// Red
			// }
		}
		bg.x = -1;
	}

	print_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

// int	loop_hook(int keycode, t_vars *vars)
// {
// 	(void)keycode;
// 	(void)vars;
// 	return (0);
// }

int	key_hook(int keycode, t_vars *vars)
{
	int	move = 4;
	// printf("key_hook func keycode: %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == W && worldMap[(vars->pos_y - move)/100][vars->pos_x/100] == 0)
		vars->pos_y -= move;
	if (keycode == A && worldMap[vars->pos_y/100][(vars->pos_x - move)/100] == 0)
		vars->pos_x -= move;
	if (keycode == S && worldMap[(vars->pos_y + vars->player_size)/100][vars->pos_x/100] == 0)
		vars->pos_y += move;
	if (keycode == D && worldMap[vars->pos_y/100][(vars->pos_x + vars->player_size)/100] == 0)
		vars->pos_x += move;
	print_img(vars);
	printf("player x:%d y:%d\n", vars->pos_x, vars->pos_y);
	return (0);
}

void	init(t_vars	*vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, screenWidth, screenHeight, "Raycaster");
	vars->map_x = -1;
	vars->map_y = -1;
	vars->chunk_size = 24;
	vars->player_size = 12;
	vars->pos_x = 240;
	vars->pos_y = 240;
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

// redundant code

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