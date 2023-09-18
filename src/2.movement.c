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

void	rotation(t_vars *vars)
{
	if (vars->key.left == 1)
	{
		if (vars->pa < 0)
			vars->pa += 2 * PI;
		vars->pa -= 0.01 * ROTATION_SPEED;
		vars->pdx = cos(vars->pa);
		vars->pdy = sin(vars->pa);
	}
	if (vars->key.right == 1)
	{
		if (vars->pa > (2 * PI))
			vars->pa -= 2 * PI;
		vars->pa += 0.01 * ROTATION_SPEED;
		vars->pdx = cos(vars->pa);
		vars->pdy = sin(vars->pa);
	}
}

void	movement(t_vars *vars)
{
	// int xo	= 0; if (vars->pdx < 0) { xo =- 20 } else { xo =+ 20 }
	// int yo	= 0; if (vars->pdy < 0) { yo =- 20 } else { yo =+ 20 }
	if (vars->key.w == 1)
	{
		vars->px += cos(vars->pa) * vars->run;
		vars->py += sin(vars->pa) * vars->run;
	}
	if (vars->key.s == 1)
	{
		vars->px -= cos(vars->pa) * vars->run;
		vars->py -= sin(vars->pa) * vars->run;
	}
	if (vars->key.a == 1)
	{
		vars->px += cos(vars->pa - (PI / 2.0)) * vars->run;
		vars->py += sin(vars->pa - (PI / 2.0)) * vars->run;
	}
	if (vars->key.d == 1)
	{
		vars->px += cos(vars->pa + (PI / 2.0)) * vars->run;
		vars->py += sin(vars->pa + (PI / 2.0)) * vars->run;
	}
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == W)
		vars->key.w = 1;
	if (keycode == A)
		vars->key.a = 1;
	if (keycode == S)
		vars->key.s = 1;
	if (keycode == D)
		vars->key.d = 1;
	if (keycode == LEFT)
		vars->key.left = 1;
	if (keycode == RIGHT)
		vars->key.right = 1;
	if (keycode == SHIFT)
		vars->run = RUN_SPEED * 2;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == W)
		vars->key.w = 0;
	if (keycode == A)
		vars->key.a = 0;
	if (keycode == S)
		vars->key.s = 0;
	if (keycode == D)
		vars->key.d = 0;
	if (keycode == LEFT)
		vars->key.left = 0;
	if (keycode == RIGHT)
		vars->key.right = 0;
	if (keycode == SHIFT)
		vars->run = RUN_SPEED;
	return (0);
}
