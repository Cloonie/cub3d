/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:10 by mliew             #+#    #+#             */
/*   Updated: 2023/09/11 15:22:10 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Initialize variables required for the start of program.
*/
void	start_init(t_vars	*vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, screenWidth, screenHeight, "cub3d");
	vars->player_size = 10;
	vars->px = 64+32;
	vars->py = (6*64)+32;
	vars->pa = P3; // N
	// vars->pa = PI/2; // S
	// vars->pa = 0; // E
	// vars->pa = PI; // W
}

/*
	This function creates a new image and modifies each pixel to create
	one whole image onto the window, this is done so to prevent the images
	from blinking, rendering line by line which makes the game not smooth.
*/
int	put_whole_image(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx, screenWidth, screenHeight);
	movement(vars);
	rotation(vars);
	draw_bg(vars);
	draw_player(vars);
	draw_rays(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img);
}
