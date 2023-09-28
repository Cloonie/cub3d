/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.key.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:24:30 by mliew             #+#    #+#             */
/*   Updated: 2023/09/28 15:24:30 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (keycode == M)
	{
		if (vars->key.m == 0)
			vars->key.m = 1;
		else if (vars->key.m == 1)
			vars->key.m = 0;
	}
	if (keycode == E)
		open_close_door(vars);
	return (0);
}
