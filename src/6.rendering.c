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

#include "../includes/cub3d.h"

void	render_ceiling(t_vars *vars, t_ray *ray, t_render *render)
{
	t_line	line;

	line = set_line(ray->r + (mapY * mapS), 0,
			ray->r + (mapY * mapS), render->lineO);
	draw_line(vars, &line, rgb_to_hex(vars->mapdata.ceiling_color[0],
			vars->mapdata.ceiling_color[1],
			vars->mapdata.ceiling_color[2]));
}

void	render_floor(t_vars *vars, t_ray *ray, t_render *render)
{
	t_line	line;

	line = set_line(ray->r + (mapY * mapS), (render->lineH + render->lineO),
			ray->r + (mapY * mapS), (render->lineH + (render->lineO * 2)));
	draw_line(vars, &line, rgb_to_hex(vars->mapdata.floor_color[0],
			vars->mapdata.floor_color[1],
			vars->mapdata.floor_color[2]));
}

void	render_walls(t_vars *vars, t_ray *ray, t_render *render)
{
	t_pixel	tex;

	render->ty = render->ty_off * render->ty_step;
	if (ray->shade == 1)
	{
		render->tx = (int)(ray->rx) % 64;
		if (ray->ra < PI)
		{
			render->tx = 63 - render->tx; // flip image horizontally
			tex.addr = mlx_get_data_addr(vars->mapdata.north_texture,
					&tex.bits_per_pixel, &tex.size_line, &tex.endian);
		}
		if (ray->ra > PI)
			tex.addr = mlx_get_data_addr(vars->mapdata.south_texture,
					&tex.bits_per_pixel, &tex.size_line, &tex.endian);
	}
	else
	{
		render->tx = (int)(ray->ry) % 64;
		if (ray->ra > D90 && ray->ra < D270)
		{
			render->tx = 63 - render->tx; // flip image horizontally
			tex.addr = mlx_get_data_addr(vars->mapdata.east_texture,
					&tex.bits_per_pixel, &tex.size_line, &tex.endian);
		}
		if (ray->ra < D90 || ray->ra > D270)
			tex.addr = mlx_get_data_addr(vars->mapdata.west_texture,
					&tex.bits_per_pixel, &tex.size_line, &tex.endian);
	}
	for (int y = 0; y < render->lineH; y++)
	{
		tex.pos = (int)render->ty * tex.size_line + (int)render->tx
			* (tex.bits_per_pixel / 8);
		draw_pixel(vars, ray->r + (mapY * mapS), (y + render->lineO),
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
		render->ca += 2 * PI;
	if (render->ca > 2 * PI)
		render->ca -= 2 * PI;
	ray->tdis = ray->tdis * cos(render->ca);
	render->lineH = (mapS * rendersize) / ray->tdis;
	render->ty_step = 64 / (float)render->lineH;
	render->ty_off = 0;
	if (render->lineH > rendersize)
	{
		render->ty_off = (render->lineH - rendersize) / 2;
		render->lineH = rendersize;
	}
	render->lineO = (rendersize / 2) - render->lineH / 2;

	render_walls(vars, ray, render);
	render_ceiling(vars, ray, render);
	render_floor(vars, ray, render);
}
