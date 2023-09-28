/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.movement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:24:44 by mliew             #+#    #+#             */
/*   Updated: 2023/09/28 15:24:44 by mliew            ###   ########.fr       */
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

void	up_down(t_vars *vars, char **map, int xo, int yo)
{
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
}

void	left_right(t_vars *vars, char **map)
{
	float	new_px;
	float	new_py;

	if (vars->key.a == 1)
	{
		new_px = vars->px - cos(vars->pa + D90) * vars->key.shift;
		new_py = vars->py - sin(vars->pa + D90) * vars->key.shift;
		if (map[(int)(new_py / mapS)][(int)(new_px / mapS)] == '0'
			|| map[(int)(new_py / mapS)][(int)(new_px / mapS)] == '3')
		{
			vars->px = new_px;
			vars->py = new_py;
		}
	}
	else if (vars->key.d == 1)
	{
		new_px = vars->px + cos(vars->pa + D90) * vars->key.shift;
		new_py = vars->py + sin(vars->pa + D90) * vars->key.shift;
		if (map[(int)(new_py / mapS)][(int)(new_px / mapS)] == '0'
			|| map[(int)(new_py / mapS)][(int)(new_px / mapS)] == '3')
		{
			vars->px = new_px;
			vars->py = new_py;
		}
	}
}

void	movement(t_vars *vars, char **map, int xo, int yo)
{
	if (vars->pdx < 0)
		xo -= 5;
	else
		xo += 5;
	if (vars->pdy < 0)
		yo -= 5;
	else
		yo += 5;
	up_down(vars, map, xo, yo);
	left_right(vars, map);
}
