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
	int		bits_per_pixel = 0;
	int		size_line = 0;
	int		endian = 0;
	char	*pixel_data;

	vars->img = mlx_new_image(vars->mlx, screenWidth, screenHeight);
	pixel_data = mlx_get_data_addr(vars->img, &bits_per_pixel, &size_line, &endian);

	t_pixel bg;
	bg.addr = mlx_get_data_addr(vars->bg_img, &bg.bits_per_pixel, &bg.size_line, &bg.endian);

	int x = vars->pos_x;
	int y = vars->pos_y;
	while (y < (vars->pos_y + vars->pos_size))
	{
		while (x < (vars->pos_x + vars->pos_size))
		{
			int offset = y * size_line + x * (bits_per_pixel / 8);
			int pos = y * bg.size_line + x * (bg.bits_per_pixel / 8);
			pixel_data[offset] = bg.addr[pos];     // Blue
			pixel_data[offset + 1] = bg.addr[pos + 1]; // Green
			pixel_data[offset + 2] = bg.addr[pos + 2]; // Red
			pixel_data[offset + 3] = bg.addr[pos + 3]; // Alpha
			x++;
		}
		x = vars->pos_x;
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);

	// int pos = (y * size_line + x * (bits_per_pixel / 8));

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
	vars->img_size = 24;
	vars->pos_size = 50;
	vars->pos_x = 48;
	vars->pos_y = 48;
	vars->bg_img = mlx_xpm_file_to_image(vars->mlx, "background.xpm", &vars->img_size, &vars->img_size);
	// vars->pos_img = mlx_xpm_file_to_image(vars->mlx, "dot.xpm", &vars->pos_size, &vars->pos_size);
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
