/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.raycasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:24:18 by mliew             #+#    #+#             */
/*   Updated: 2023/09/11 15:24:18 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rays(t_vars *vars, t_ray *ray)
{
	ray->r = -1;
	ray->rx = 0;
	ray->ry = 0;
	ray->xo = 0;
	ray->yo = 0;
	ray->tdis = 0;
	ray->shade = 1;
	// starting angle position from middle minus 30 radians then cast rays in 60 radians
	ray->ra = vars->pa - (DR * 30);
	// resets angle if exceeds 360 or less than 0
	if (ray->ra < 0)
		ray->ra += 2 * PI;
	if (ray->ra > 2 * PI)
		ray->ra -= 2 * PI;
}

void	horizon_rays(t_vars *vars, t_ray *ray)
{
	ray->dof = 0;
	ray->hdis = INT_MAX;
	ray->hx = vars->px;
	ray->hy = vars->py;
	ray->a_tan = -1 / tan(ray->ra);
	if (ray->ra > PI) // looking up
	{
		ray->ry = (((int)vars->py / mapS) * mapS) - 0.0001;
		ray->rx = (vars->py - ray->ry) * ray->a_tan + vars->px;
		ray->yo = -mapS;
		ray->xo = -ray->yo * ray->a_tan;
	}
	if (ray->ra < PI) // looking down
	{
		ray->ry = (((int)vars->py / mapS) * mapS) + mapS;
		ray->rx = (vars->py - ray->ry) * ray->a_tan + vars->px;
		ray->yo = mapS;
		ray->xo = -ray->yo * ray->a_tan;
	}
	// if (ray->ra == 0 || ray->ra == PI) // looking left or right
	// {
	// 	ray->rx = vars->px;
	// 	ray->ry = vars->py;
	// 	ray->dof = 8;
	// }
}

void	horizon_dof(t_vars *vars, t_ray *ray)
{
	while (ray->dof < 8)
	{
		ray->mx = (int)(ray->rx) / mapS;
		ray->my = (int)(ray->ry) / mapS;
		ray->mp = ray->my * mapX + ray->mx;
		if (ray->mp > 0 && ray->mx < mapX && ray->my < mapY
			&& vars->mapdata.map[ray->my][ray->mx] == '1')
		{
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->hdis = dist(vars->px, vars->py, ray->hx, ray->hy);
			ray->dof = 8;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	vertical_rays(t_vars *vars, t_ray *ray)
{
	ray->dof = 0;
	ray->vdis = INT_MAX;
	ray->vx = vars->px;
	ray->vy = vars->py;
	ray->n_tan = -tan(ray->ra);
	if (ray->ra > D90 && ray->ra < D270) // looking left
	{
		ray->rx = (((int)vars->px / mapS) * mapS) - 0.0001;
		ray->ry = (vars->px - ray->rx) * ray->n_tan + vars->py;
		ray->xo = -mapS;
		ray->yo = -ray->xo * ray->n_tan;
	}
	if (ray->ra < D90 || ray->ra > D270) // looking right
	{
		ray->rx = (((int)vars->px / mapS) * mapS) + mapS;
		ray->ry = (vars->px - ray->rx) * ray->n_tan + vars->py;
		ray->xo = mapS;
		ray->yo = -ray->xo * ray->n_tan;
	}
	// if (ray->ra == 0 || ray->ra == PI) // looking up or down
	// {
	// 	ray->rx = vars->px;
	// 	ray->ry = vars->py;
	// 	ray->dof = 8;
	// }
}

void	vertical_dof(t_vars *vars, t_ray *ray)
{
	while (ray->dof < 8)
	{
		ray->mx = (int)(ray->rx) / mapS;
		ray->my = (int)(ray->ry) / mapS;
		ray->mp = ray->my * mapX + ray->mx;
		if (ray->mp > 0 && ray->mx < mapX && ray->my < mapY
			&& vars->mapdata.map[ray->my][ray->mx] == '1')
		{
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->vdis = dist(vars->px, vars->py, ray->vx, ray->vy);
			ray->dof = 8;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	get_nearest_ray(t_vars *vars, t_ray *ray)
{
	t_line	line;

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
	if (vars->key.m == 1)
	{
		line = set_line(vars->px, vars->py, ray->rx, ray->ry);
		draw_line(vars, &line, 0xFF0000);
	}
}

void	raycasting(t_vars *vars)
{
	t_ray	*ray;

	ray = &vars->ray;
	init_rays(vars, ray);
	while (++ray->r < screenWidth) // loop for each ray
	{
		horizon_rays(vars, ray);
		horizon_dof(vars, ray);
		vertical_rays(vars, ray);
		vertical_dof(vars, ray);
		get_nearest_ray(vars, ray);
		rendering(vars, ray);
		ray->ra += DR / RAYOFFSET;
		if (ray->ra < 0)
			ray->ra += 2 * PI;
		if (ray->ra > 2 * PI)
			ray->ra -= 2 * PI;
	}
}

void	draw_rays(t_vars *vars)
{
	t_ray	*ray;

	ray = &vars->ray;
	init_rays(vars, ray);
	while (++ray->r < screenWidth) // loop for each ray
	{
		horizon_rays(vars, ray);
		horizon_dof(vars, ray);
		vertical_rays(vars, ray);
		vertical_dof(vars, ray);
		get_nearest_ray(vars, ray);
		ray->ra += DR / RAYOFFSET;
		if (ray->ra < 0)
			ray->ra += 2 * PI;
		if (ray->ra > 2 * PI)
			ray->ra -= 2 * PI;
	}
}
