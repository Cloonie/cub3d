/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.raycasting2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:03:22 by mliew             #+#    #+#             */
/*   Updated: 2023/09/28 16:03:22 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// if (vars->key.m == 1)
// {
// 	line = set_line(vars->px, vars->py, ray->rx, ray->ry);
// 	draw_line(vars, &line, 0xFF0000);
// }
void	get_nearest_ray(t_vars *vars, t_ray *ray)
{
	(void)vars;
	if (ray->vdis < ray->hdis)
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->tdis = ray->vdis;
		ray->shade = 0.5;
	}
	if (ray->hdis < ray->vdis)
	{
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->tdis = ray->hdis;
		ray->shade = 1;
	}
}

/*
	This function is the main function that does raycasting on 2d space
	into rendering it into a 3d-looking image
*/
void	raycasting(t_vars *vars)
{
	t_ray	*ray;

	ray = &vars->ray;
	init_rays(vars, ray);
	while (++ray->r < vars->win_width)
	{
		horizon_rays(vars, ray);
		horizon_dof(vars, ray);
		vertical_rays(vars, ray);
		vertical_dof(vars, ray);
		get_nearest_ray(vars, ray);
		rendering(vars, ray);
		ray->ra += DR / (vars->win_width / 60);
		if (ray->ra < 0)
			ray->ra += 2 * D180_PI;
		if (ray->ra > 2 * D180_PI)
			ray->ra -= 2 * D180_PI;
	}
}

/*
	This function is to draw rays even after rendering on the in game map
*/
void	draw_rays(t_vars *vars)
{
	t_ray	*ray;

	ray = &vars->ray;
	init_rays(vars, ray);
	while (++ray->r < vars->win_width)
	{
		horizon_rays(vars, ray);
		horizon_dof(vars, ray);
		vertical_rays(vars, ray);
		vertical_dof(vars, ray);
		get_nearest_ray(vars, ray);
		ray->ra += DR / (vars->win_width / 60);
		if (ray->ra < 0)
			ray->ra += 2 * D180_PI;
		if (ray->ra > 2 * D180_PI)
			ray->ra -= 2 * D180_PI;
	}
}
