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

int	key_hook(int keycode, t_vars *vars)
{
	printf("key_hook func keycode: %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }
	// img.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	// 							&img.endian);
	// my_mlx_pixel_put(&img, 200, 200, 0x00FF0000);
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

int	main(void)
{
	t_vars	vars;
	// t_data	img;
	int mapX = 20;
	int mapY = 20;
	int img_size = 20;
	int i = -1;
	int j = -1;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Raycaster");
	mlx_key_hook(vars.win, key_hook, &vars);

	while (mapY * ++i < screenHeight)
	{
		while (mapX * ++j < screenWidth)
		{
			mlx_put_image_to_window(vars.mlx, vars.win, mlx_xpm_file_to_image(vars.mlx, "whitebg.xpm", &img_size, &img_size), mapX * j, mapY * i);
		}
		j = -1;
	}

	mlx_loop(vars.mlx);
}
