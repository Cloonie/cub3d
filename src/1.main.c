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

#include "cub3d.h"

/*
	Initialize variables required for the start of program.
*/
void	start_init(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, screenWidth, screenHeight, "cub3d");
	vars->player_size = 10;
	vars->px = mapS+32;
	vars->py = (6*mapS)+32;
	vars->key.w = 0;
	vars->key.a = 0;
	vars->key.s = 0;
	vars->key.d = 0;
	vars->key.left = 0;
	vars->key.right = 0;
	vars->key.shift = RUN_SPEED;
	vars->key.e = 0;
	vars->key.m = 0;

	// vars->pa = D270; // N
	// vars->pa = PI/2; // S
	vars->pa = 0; // E
	// vars->pa = PI; // W
}

/*
	This function creates a new image and modifies each pixel to create
	one whole image onto the window, this is done so to prevent the images
	from blinking, rendering line by line which makes the game not smooth.
*/
int	put_whole_image(t_vars *vars)
{
	t_line	line;

	vars->img = mlx_new_image(vars->mlx, screenWidth, screenHeight);
	movement(vars);
	rotation(vars);
	raycasting(vars);
	if (vars->key.m == 1)
	{
		draw_bg(vars);
		draw_player(vars);
		draw_rays(vars);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars		vars;

	if (argc != 2)
	{
		printf("Error, please input ./cub3d [path_to_map_file]\n");
		// return (0);
	}
	start_init(&vars);
	open_map_file(&vars);
	mlx_loop_hook(vars.mlx, put_whole_image, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, key_release, &vars);
	mlx_hook(vars.win, 17, 0, window_close, &vars);
	mlx_loop(vars.mlx);
}
