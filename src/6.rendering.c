/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:16 by mliew             #+#    #+#             */
/*   Updated: 2023/09/11 15:22:16 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ceiling(t_vars *vars, t_ray *ray, t_render *render)
{
	t_line	line;

	line = set_line(ray->r, 0,
			ray->r, render->lineO);
	draw_line(vars, &line, rgb_to_hex(vars->mapdata.ceiling_color[0],
			vars->mapdata.ceiling_color[1],
			vars->mapdata.ceiling_color[2]));
}

void	render_floor(t_vars *vars, t_ray *ray, t_render *render)
{
	t_line	line;

	line = set_line(ray->r, (render->lineH + render->lineO),
			ray->r, (render->lineH + (render->lineO * 2)));
	draw_line(vars, &line, rgb_to_hex(vars->mapdata.floor_color[0],
			vars->mapdata.floor_color[1],
			vars->mapdata.floor_color[2]));
}

void	texture_ns(t_vars *vars, t_ray *ray, t_render *render, t_pixel *tex)
{
	render->tx = (int)(ray->rx) % textureS;
	if (ray->ra < D180_PI)
	{
		render->tx = (textureS - 1) - render->tx; // flip image horizontally
		tex->addr = mlx_get_data_addr(vars->mapdata.north_texture,
				&tex->bits_per_pixel, &tex->size_line, &tex->endian);
	}
	if (ray->ra > D180_PI)
		tex->addr = mlx_get_data_addr(vars->mapdata.south_texture,
				&tex->bits_per_pixel, &tex->size_line, &tex->endian);
	if (ray->hd == 1)
		tex->addr = mlx_get_data_addr(vars->mapdata.door_texture,
				&tex->bits_per_pixel, &tex->size_line, &tex->endian);
}

void	texture_we(t_vars *vars, t_ray *ray, t_render *render, t_pixel *tex)
{
	render->tx = (int)(ray->ry) % textureS;
	if (ray->ra > D90 && ray->ra < D270)
	{
		render->tx = (textureS - 1) - render->tx; // flip image horizontally
		tex->addr = mlx_get_data_addr(vars->mapdata.east_texture,
				&tex->bits_per_pixel, &tex->size_line, &tex->endian);
	}
	if (ray->ra < D90 || ray->ra > D270)
		tex->addr = mlx_get_data_addr(vars->mapdata.west_texture,
				&tex->bits_per_pixel, &tex->size_line, &tex->endian);
	if (ray->vd == 1)
		tex->addr = mlx_get_data_addr(vars->mapdata.door_texture,
				&tex->bits_per_pixel, &tex->size_line, &tex->endian);
}

void	render_walls(t_vars *vars, t_ray *ray, t_render *render)
{
	t_pixel	tex;
	int		y;

	y = -1;
	render->ty = render->ty_off * render->ty_step;
	// printf("debug: %d\n", ray->r);
	// printf("|%c|, my: %d, mx %d\n", vars->mapdata.map[ray->my][ray->mx], ray->my, ray->mx);
	if (ray->shade == 1)
		texture_ns(vars, ray, render, &tex);
	else
		texture_we(vars, ray, render, &tex);
	while (++y < render->lineH)
	{
		tex.pos = (int)render->ty * tex.size_line + (int)render->tx
			* (tex.bits_per_pixel / 8);
		draw_pixel(vars, ray->r, (y + render->lineO),
			rgb_to_hex(tex.addr[tex.pos + 2], tex.addr[tex.pos + 1],
				tex.addr[tex.pos]));
		render->ty += render->ty_step;
	}
}

void	rendering(t_vars *vars, t_ray *ray)
{
	t_render	*render;

	render = &vars->render;
	render->ca = vars->pa - ray->ra;
	if (render->ca < 0)
		render->ca += 2 * D180_PI;
	if (render->ca > 2 * D180_PI)
		render->ca -= 2 * D180_PI;
	ray->tdis = ray->tdis * cos(render->ca);
	render->lineH = (textureS * vars->win_height) / ray->tdis;
	render->ty_step = textureS / (float)render->lineH;
	render->ty_off = 0;
	if (render->lineH > vars->win_height)
	{
		render->ty_off = (render->lineH - vars->win_height) / 2;
		render->lineH = vars->win_height;
	}
	render->lineO = (vars->win_height / 2) - render->lineH / 2;
	render_ceiling(vars, ray, render);
	render_walls(vars, ray, render);
	render_floor(vars, ray, render);
}
