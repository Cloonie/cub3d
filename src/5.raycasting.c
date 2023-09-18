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

void	init_rays(t_vars *vars, t_ray *ray)
{
	ray->r = -1;
	ray->rx = 0;
	ray->ry = 0;
	ray->xo = 0;
	ray->yo = 0;
	ray->tdis = 0;

	// starting angle position
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
		ray->ry = (((int)vars->py >> 6) << 6) - 0.0001;
		ray->rx = (vars->py - ray->ry) * ray->a_tan + vars->px;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->a_tan;
	}
	if (ray->ra < PI) // looking down
	{
		ray->ry = (((int)vars->py >> 6) << 6) + 64;
		ray->rx = (vars->py - ray->ry) * ray->a_tan + vars->px;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->a_tan;
	}
	if (ray->ra == 0 || ray->ra == PI) // looking left or right
	{
		ray->rx = vars->px;
		ray->ry = vars->py;
		ray->dof = 8;
	}
}

void	horizon_dof(t_vars *vars, t_ray *ray)
{
	while (ray->dof < 8)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * mapX + ray->mx;
		if (ray->mp > 0 && ray->mx < mapX && ray->my < mapY
			&& map[ray->my][ray->mx] == 1)
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
	if (ray->ra > P2 && ray->ra < P3) // looking left
	{
		ray->rx = (((int)vars->px >> 6) << 6) - 0.0001;
		ray->ry = (vars->px - ray->rx) * ray->n_tan + vars->py;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->n_tan;
	}
	if (ray->ra < P2 || ray->ra > P3) // looking right
	{
		ray->rx = (((int)vars->px >> 6) << 6) + 64;
		ray->ry = (vars->px - ray->rx) * ray->n_tan + vars->py;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->n_tan;
	}
	if (ray->ra == 0 || ray->ra == PI) // looking up or down
	{
		ray->rx = vars->px;
		ray->ry = vars->py;
		ray->dof = 8;
	}
}

void	vertical_dof(t_vars *vars, t_ray *ray)
{
	while (ray->dof < 8)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * mapX + ray->mx;
		if (ray->mp > 0 && ray->mx < mapX && ray->my < mapY
			&& map[ray->my][ray->mx] == 1)
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

void	draw_rays(t_vars *vars)
{
	t_ray	ray;

	init_rays(vars, &ray);
	// loop for each ray
	while (++ray.r < 720)
	{
		horizon_rays(vars, &ray);
		horizon_dof(vars, &ray);
		vertical_rays(vars, &ray);
		vertical_dof(vars, &ray);

		int shade = 1;
		if (ray.vdis < ray.hdis)
		{
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.tdis = ray.vdis;
			shade = 0.5;
		}
		if (ray.hdis < ray.vdis)
		{
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.tdis = ray.hdis;
		}

		t_line	line;
		line = set_line(vars->px, vars->py, ray.rx, ray.ry);
		draw_line(vars, &line, 0xFF0000);

		// draw 3d / rendering 3d
		float ca = vars->pa - ray.ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		ray.tdis = ray.tdis * cos(ca);
		float lineH = (mapS * rendersize) / ray.tdis;
		float	ty_step = 64/(float)lineH;
		float	ty_off = 0;
		if (lineH > rendersize)
		{
			ty_off = (lineH - rendersize)/2.0;
			lineH = rendersize;
		}
		float lineO = (rendersize / 2) - lineH / 2;

		// walls
		float	ty = ty_off * ty_step;
		float	tx;
		t_pixel	tex;
		if (shade == 1)
		{
			tx = (int)(ray.rx) % 64;
			if (ray.ra < PI)
			{
				tx = 63 - tx; // flip image horizontally
				tex.addr = mlx_get_data_addr(vars->mapdata.north_texture,
					&tex.bits_per_pixel, &tex.size_line, &tex.endian);
			}
			if (ray.ra > PI)
				tex.addr = mlx_get_data_addr(vars->mapdata.south_texture,
					&tex.bits_per_pixel, &tex.size_line, &tex.endian);
		}
		else
		{
			tx = (int)(ray.ry) % 64;
			if (ray.ra > P2 && ray.ra < P3)
			{
				tx = 63 - tx; // flip image horizontally
				tex.addr = mlx_get_data_addr(vars->mapdata.east_texture,
					&tex.bits_per_pixel, &tex.size_line, &tex.endian);
			}
			if (ray.ra < P2 || ray.ra > P3)
				tex.addr = mlx_get_data_addr(vars->mapdata.west_texture,
					&tex.bits_per_pixel, &tex.size_line, &tex.endian);
		}
		for (int y = 0; y < lineH; y++)
		{
			tex.pos = (int)ty * tex.size_line + (int)tx * (tex.bits_per_pixel / 8);
			draw_pixel(vars, ray.r+(mapY*mapS)+16, y+lineO, rgb_to_hex(tex.addr[tex.pos + 2], tex.addr[tex.pos + 1], tex.addr[tex.pos]));
			ty += ty_step;
		}

		// ceiling
		line = set_line(ray.r+(mapY*mapS)+16, 0, ray.r+(mapY*mapS)+16, lineO);
		draw_line(vars, &line, rgb_to_hex(vars->mapdata.ceiling_color[0],
				vars->mapdata.ceiling_color[1],
				vars->mapdata.ceiling_color[2]));

		// floor
		line = set_line(ray.r+(mapY*mapS)+16, lineH+lineO, ray.r+(mapY*mapS)+16, lineH+lineO+lineO);
		draw_line(vars, &line, rgb_to_hex(vars->mapdata.floor_color[0],
				vars->mapdata.floor_color[1],
				vars->mapdata.floor_color[2]));

		// loop for each ray at next radian
		ray.ra += DR / 12;
		if (ray.ra < 0)
			ray.ra += 2 * PI;
		if (ray.ra > 2 * PI)
			ray.ra -= 2 * PI;
	}
}
