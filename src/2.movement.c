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

#include "cub3d.h"

void	rotation(t_vars *vars)
{
	if (vars->key.left == 1)
	{
		if (vars->pa < 0)
			vars->pa += 2 * D180_PI;
		vars->pa -= 0.01 * ROTATION_SPEED;
		vars->pdx = cos(vars->pa);
		vars->pdy = sin(vars->pa);
	}
	if (vars->key.right == 1)
	{
		if (vars->pa > (2 * D180_PI))
			vars->pa -= 2 * D180_PI;
		vars->pa += 0.01 * ROTATION_SPEED;
		vars->pdx = cos(vars->pa);
		vars->pdy = sin(vars->pa);
	}
}

void	movement(t_vars *vars)
{
	char	**map;
	int xo	= 0;
	int yo	= 0;

	map = vars->mapdata.map;
	if (vars->pdx < 0)
		xo -= 20;
	else
		xo += 20;
	if (vars->pdy < 0)
		yo -= 20;
	else
		yo += 20;
	if (vars->key.w == 1)
	{
		if (map[((int)vars->py) / mapS][((int)vars->px + xo) / mapS] == '0'
			|| map[((int)vars->py) / mapS][((int)vars->px + xo) / mapS] == '3')
			vars->px += cos(vars->pa) * vars->key.shift;
		if (map[((int)vars->py + yo) / mapS][((int)vars->px) / mapS] == '0'
			|| map[((int)vars->py + yo) / mapS][((int)vars->px) / mapS] == '3')
			vars->py += sin(vars->pa) * vars->key.shift;
	}
	if (vars->key.s == 1)
	{
		if (map[((int)vars->py) / mapS][((int)vars->px - xo) / mapS] == '0'
			|| map[((int)vars->py) / mapS][((int)vars->px - xo) / mapS] == '3')
			vars->px -= cos(vars->pa) * vars->key.shift;
		if (map[((int)vars->py - yo) / mapS][((int)vars->px) / mapS] == '0'
			|| map[((int)vars->py - yo) / mapS][((int)vars->px) / mapS] == '3')
			vars->py -= sin(vars->pa) * vars->key.shift;
	}
	if (vars->key.a == 1)
	{
		if (map[((int)vars->py) / mapS][((int)vars->px + xo -1) / mapS] == '0'
			&& map[((int)vars->py) / mapS][((int)vars->px - xo -1) / mapS] == '0')
			vars->px += cos(vars->pa - (D180_PI / 2.0)) * vars->key.shift;
		if (map[((int)vars->py + yo -1) / mapS][((int)vars->px) / mapS] == '0'
			&& map[((int)vars->py - yo -1) / mapS][((int)vars->px) / mapS] == '0')
			vars->py += sin(vars->pa - (D180_PI / 2.0)) * vars->key.shift;
	}
	else if (vars->key.d == 1)
	{
		if (map[((int)vars->py) / mapS][((int)vars->px + xo +1) / mapS] == '0'
			&& map[((int)vars->py) / mapS][((int)vars->px - xo +1) / mapS] == '0')
			vars->px += cos(vars->pa + (D180_PI / 2.0)) * vars->key.shift;
		if (map[((int)vars->py + yo +1) / mapS][((int)vars->px) / mapS] == '0'
			&& map[((int)vars->py - yo +1) / mapS][((int)vars->px) / mapS] == '0')
			vars->py += sin(vars->pa + (D180_PI / 2.0)) * vars->key.shift;
	}
}

void	open_close_door(t_vars *vars)
{
	int	xo;
	int	yo;

	xo = 0;
	yo = 0;
	if (vars->pdx < 0)
		xo -= 25;
	else
		xo += 25;
	if (vars->pdy < 0)
		yo -= 25;
	else
		yo += 25;
	if (vars->mapdata.map[((int)vars->py + yo) / mapS]
		[((int)vars->px + xo) / mapS] == '2')
		vars->mapdata.map[((int)vars->py + yo) / mapS]
		[((int)vars->px + xo) / mapS] = '3';
	else if (vars->mapdata.map[(int)vars->py / mapS]
		[(int)vars->px / mapS] != '3'
		&& vars->mapdata.map[((int)vars->py + yo) / mapS]
		[((int)vars->px + xo) / mapS] == '3')
		vars->mapdata.map[((int)vars->py + yo) / mapS]
		[((int)vars->px + xo) / mapS] = '2';
}

int	key_press(int keycode, t_vars *vars)
{
	// printf("keycode %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		printf("Window closed: ESC button\n");
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
		vars->key.shift = RUN_SPEED * 2;
	if (keycode == E)
		open_close_door(vars);
	if (keycode == M)
	{
		if (vars->key.m == 0)
			vars->key.m = 1;
		else if (vars->key.m == 1)
			vars->key.m = 0;
	}
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
		vars->key.shift = RUN_SPEED;
	if (keycode == E)
		vars->key.e = 0;
	return (0);
}
