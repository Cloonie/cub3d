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

#include "../includes/cub3d.h"

void	init_rays(t_ray *ray)
{
	// ray->r = 0;
	// ray->mx = 0;
	// ray->my = 0;
	// ray->mp = 0;
	// ray->dof = 0;
	ray->rx = 0;
	ray->ry = 0;
	// ray->ra = 0;
	ray->xo = 0;
	ray->yo = 0;
	// ray->hdis = 0;
	// ray->hx = 0;
	// ray->hy = 0;
	// ray->a_tan = 0;
	// ray->vdis = 0;
	// ray->vx = 0;
	// ray->vy = 0;
	// ray->n_tan = 0;
	ray->tdis = 0;
}

void	draw_rays(t_vars *vars)
{
	t_ray	ray;
	t_line	line;

	init_rays(&ray);
	ray.ra = vars->pa - (DR * 30);
	if (ray.ra < 0)
		ray.ra += 2 * PI;
	if (ray.ra > 2 * PI)
		ray.ra -= 2 * PI;

	// loop for each ray
	ray.r = -1;
	while (++ray.r < 360)
	{
		// horizonal lines
		ray.dof = 0;
		ray.hdis = INT_MAX;
		ray.hx = vars->px;
		ray.hy = vars->py;
		ray.a_tan = -1 / tan(ray.ra);
		if (ray.ra > PI) // looking up
		{
			ray.ry = (((int)vars->py >> 6) << 6) - 0.0001;
			ray.rx = (vars->py - ray.ry) * ray.a_tan + vars->px;
			ray.yo = -64;
			ray.xo = -ray.yo * ray.a_tan;
		}
		if (ray.ra < PI) // looking down
		{
			ray.ry = (((int)vars->py >> 6) << 6) + 64;
			ray.rx = (vars->py - ray.ry) * ray.a_tan + vars->px;
			ray.yo = 64;
			ray.xo = -ray.yo * ray.a_tan;
		}
		if (ray.ra == 0 || ray.ra == PI) // looking left or right
		{
			ray.rx = vars->px;
			ray.ry = vars->py;
			ray.dof = 8;
		}
		while (ray.dof < 8)
		{
			ray.mx = (int)(ray.rx) >> 6;
			ray.my = (int)(ray.ry) >> 6;
			ray.mp = ray.my * mapX + ray.mx;
			if (ray.mp > 0 && ray.mx < mapX && ray.my < mapY
				&& map[ray.my][ray.mx] == 1)
			{
				ray.hx = ray.rx;
				ray.hy = ray.ry;
				ray.hdis = dist(vars->px, vars->py, ray.hx, ray.hy);
				ray.dof = 8;
			}
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
			}
		}
		// draw_line(vars, ray.rx, ray.ry, 0x0000FF);

		// vertical lines
		ray.dof = 0;
		ray.vdis = INT_MAX;
		ray.vx = vars->px;
		ray.vy = vars->py;
		ray.n_tan = -tan(ray.ra);
		if (ray.ra > P2 && ray.ra < P3) // looking left
		{
			ray.rx = (((int)vars->px >> 6) << 6) - 0.0001;
			ray.ry = (vars->px - ray.rx) * ray.n_tan + vars->py;
			ray.xo = -64;
			ray.yo = -ray.xo * ray.n_tan;
		}
		if (ray.ra < P2 || ray.ra > P3) // looking right
		{
			ray.rx = (((int)vars->px >> 6) << 6) + 64;
			ray.ry = (vars->px - ray.rx) * ray.n_tan + vars->py;
			ray.xo = 64;
			ray.yo = -ray.xo * ray.n_tan;
		}
		if (ray.ra == 0 || ray.ra == PI) // looking up or down
		{
			ray.rx = vars->px;
			ray.ry = vars->py;
			ray.dof = 8;
		}
		while (ray.dof < 8)
		{
			ray.mx = (int)(ray.rx) >> 6;
			ray.my = (int)(ray.ry) >> 6;
			ray.mp = ray.my * mapX + ray.mx;
			if (ray.mp > 0 && ray.mx < mapX && ray.my < mapY
				&& map[ray.my][ray.mx] == 1)
			{
				ray.vx = ray.rx;
				ray.vy = ray.ry;
				ray.vdis = dist(vars->px, vars->py, ray.vx, ray.vy);
				ray.dof = 8;
			}
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
			}
		}
		if (ray.vdis < ray.hdis)
		{
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.tdis = ray.vdis;
			line.red = 255;
			line.green = 0;
			line.blue = 0;
		}
		if (ray.hdis < ray.vdis)
		{
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.tdis = ray.hdis;
			line.red = 150;
			line.green = 0;
			line.blue = 0;
		}
		// printf("vertical rx: %f ry: %f\n", ray.rx, ray.ry);
		line = set_line(vars->px, vars->py, ray.rx, ray.ry);
		draw_line(vars, &line);

		// draw 3d / rendering 3d
		float ca = vars->pa - ray.ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		ray.tdis = ray.tdis * cos(ca);
		float lineH = (mapS * 700) / ray.tdis;
		if (lineH > 700)
			lineH = 700;
		float lineO = 350 - lineH / 2;
		for (int d = 0; d < 2; d++)
		{
			// walls
			line = set_line(ray.r*2+d+(mapY*mapS)+16, lineO, ray.r*2+d+(mapY*mapS)+16, lineH+lineO);
			draw_line(vars, &line);

			// ceiling
			line = set_line(ray.r*2+d+(mapY*mapS)+16, 0, ray.r*2+d+(mapY*mapS)+16, lineO);
			line.red = vars->mapdata.ceiling_color[0];
			line.green = vars->mapdata.ceiling_color[1];
			line.blue = vars->mapdata.ceiling_color[2];
			draw_line(vars, &line);

			// floor
			line = set_line(ray.r*2+d+(mapY*mapS)+16, lineH+lineO, ray.r*2+d+(mapY*mapS)+16, lineH+lineO+lineO);
			line.red = vars->mapdata.floor_color[0];
			line.green = vars->mapdata.floor_color[1];
			line.blue = vars->mapdata.floor_color[2];
			draw_line(vars, &line);
		}

		// loop for each ray at next radian
		ray.ra += DR / 6;
		if (ray.ra < 0)
			ray.ra += 2 * PI;
		if (ray.ra > 2 * PI)
			ray.ra -= 2 * PI;
	}
}
