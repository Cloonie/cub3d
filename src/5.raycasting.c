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

// starting angle position from middle minus 30 radians
// then cast rays in 60 radians
// resets angle if exceeds 360 or less than 0
void	init_rays(t_vars *vars, t_ray *ray)
{
	ray->r = -1;
	ray->rx = 0;
	ray->ry = 0;
	ray->xo = 0;
	ray->yo = 0;
	ray->tdis = 0;
	ray->shade = 1;
	ray->ra = vars->pa - (DR * 30);
	if (ray->ra < 0)
		ray->ra += 2 * D180_PI;
	if (ray->ra > 2 * D180_PI)
		ray->ra -= 2 * D180_PI;
}

/*
	if (ray->ra > D180_PI) looking up
	if (ray->ra < D180_PI) looking down
	if (ray->ra == 0 || ray->ra == D180_PI) looking left or right
*/
void	horizon_rays(t_vars *vars, t_ray *ray)
{
	ray->dof = 0;
	ray->hdis = INT_MAX;
	ray->hx = vars->px;
	ray->hy = vars->py;
	ray->a_tan = -1 / tan(ray->ra);
	if (ray->ra > D180_PI)
	{
		ray->ry = (((int)vars->py / mapS) * mapS) - 0.0001;
		ray->rx = (vars->py - ray->ry) * ray->a_tan + vars->px;
		ray->yo = -mapS;
		ray->xo = -ray->yo * ray->a_tan;
	}
	if (ray->ra < D180_PI)
	{
		ray->ry = (((int)vars->py / mapS) * mapS) + mapS;
		ray->rx = (vars->py - ray->ry) * ray->a_tan + vars->px;
		ray->yo = mapS;
		ray->xo = -ray->yo * ray->a_tan;
	}
	if (ray->ra == 0 || ray->ra == D180_PI)
	{
		ray->rx = vars->px;
		ray->ry = vars->py;
		ray->dof = vars->mapdata.y;
	}
}

void	horizon_dof(t_vars *vars, t_ray *ray)
{
	while (ray->dof < vars->mapdata.y)
	{
		ray->hd = 0;
		ray->mx = (int)(ray->rx) / mapS;
		ray->my = (int)(ray->ry) / mapS;
		ray->mp = ray->my * vars->mapdata.x + ray->mx;
		if (ray->mp > 0 && ray->mx < vars->mapdata.x
			&& ray->my < vars->mapdata.y
			&& (vars->mapdata.map[ray->my][ray->mx] == '1'
			|| vars->mapdata.map[ray->my][ray->mx] == '2'))
		{
			if (vars->mapdata.map[ray->my][ray->mx] == '2')
				ray->hd = 1;
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->hdis = dist(vars->px, vars->py, ray->hx, ray->hy);
			ray->dof = vars->mapdata.y;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

/*
	if (ray->ra > D90 && ray->ra < D270) looking left
	if (ray->ra < D90 || ray->ra > D270) looking right
	if (ray->ra == 0 || ray->ra == D180_PI) looking up or down
*/
void	vertical_rays(t_vars *vars, t_ray *ray)
{
	ray->dof = 0;
	ray->vdis = INT_MAX;
	ray->vx = vars->px;
	ray->vy = vars->py;
	ray->n_tan = -tan(ray->ra);
	if (ray->ra > D90 && ray->ra < D270)
	{
		ray->rx = (((int)vars->px / mapS) * mapS) - 0.0001;
		ray->ry = (vars->px - ray->rx) * ray->n_tan + vars->py;
		ray->xo = -mapS;
		ray->yo = -ray->xo * ray->n_tan;
	}
	if (ray->ra < D90 || ray->ra > D270)
	{
		ray->rx = (((int)vars->px / mapS) * mapS) + mapS;
		ray->ry = (vars->px - ray->rx) * ray->n_tan + vars->py;
		ray->xo = mapS;
		ray->yo = -ray->xo * ray->n_tan;
	}
	if (ray->ra == 0 || ray->ra == D180_PI)
	{
		ray->rx = vars->px;
		ray->ry = vars->py;
		ray->dof = vars->mapdata.x;
	}
}

void	vertical_dof(t_vars *vars, t_ray *ray)
{
	while (ray->dof < vars->mapdata.x)
	{
		ray->vd = 0;
		ray->mx = (int)(ray->rx) / mapS;
		ray->my = (int)(ray->ry) / mapS;
		ray->mp = ray->my * vars->mapdata.x + ray->mx;
		if (ray->mp > 0 && ray->mx < vars->mapdata.x
			&& ray->my < vars->mapdata.y
			&& (vars->mapdata.map[ray->my][ray->mx] == '1'
			|| vars->mapdata.map[ray->my][ray->mx] == '2'))
		{
			if (vars->mapdata.map[ray->my][ray->mx] == '2')
				ray->vd = 1;
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->vdis = dist(vars->px, vars->py, ray->vx, ray->vy);
			ray->dof = vars->mapdata.x;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}
