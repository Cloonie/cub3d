/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.movement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:59:00 by mliew             #+#    #+#             */
/*   Updated: 2023/09/11 18:59:00 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	key_hook function 
*/
int	key_hook(int keycode, t_vars *vars)
{
	// printf("key_hook func keycode: %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == LEFT)
	{
		if (vars->pa < 0)
			vars->pa += 2 * PI;
		vars->pa -= 0.05;
		vars->pdx = cos(vars->pa) * 10;
		vars->pdy = sin(vars->pa) * 10;
	}
	if (keycode == RIGHT)
	{
		if (vars->pa > (2 * PI))
			vars->pa -= 2 * PI;
		vars->pa += 0.05;
		vars->pdx = cos(vars->pa) * 10;
		vars->pdy = sin(vars->pa) * 10;
	}
	if (keycode == W)
	{
		vars->px += cos(vars->pa) * 10;
		vars->py += sin(vars->pa) * 10;
	}
	if (keycode == S)
	{
		vars->px -= cos(vars->pa) * 10;
		vars->py -= sin(vars->pa) * 10;
	}
	if (keycode == A)
	{
		vars->px += cos(vars->pa - (PI / 2.0)) * 10;
		vars->py += sin(vars->pa - (PI / 2.0)) * 10;
	}
	if (keycode == D)
	{
		vars->px += cos(vars->pa + (PI / 2.0)) * 10;
		vars->py += sin(vars->pa + (PI / 2.0)) * 10;
	}
	put_whole_image(vars);
	// printf("player x:%f y:%f\n", vars->px, vars->py);
	return (0);
}
