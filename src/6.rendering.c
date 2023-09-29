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
			ray->r, render->line_o);
	draw_line(vars, &line, rgb_to_hex(vars->mapdata.ceiling_color[0],
			vars->mapdata.ceiling_color[1],
			vars->mapdata.ceiling_color[2]));
}

void	render_floor(t_vars *vars, t_ray *ray, t_render *render)
{
	t_line	line;

	line = set_line(ray->r, (render->line_h + render->line_o),
			ray->r, (render->line_h + (render->line_o * 2)));
	draw_line(vars, &line, rgb_to_hex(vars->mapdata.floor_color[0],
			vars->mapdata.floor_color[1],
			vars->mapdata.floor_color[2]));
}

/*
	Assigns the south texture according to the angle facing
	and assigns the opposite texture (north) fliped horizontally
	and assigns the door texture for horizonal lines on 2d space
*/
void	texture_ns(t_vars *vars, t_ray *ray, t_render *render, t_pixel *tex)
{
	render->tx = (int)(ray->rx) % MAP_S;
	if (ray->ra < D180_PI)
	{
		render->tx = (MAP_S - 1) - render->tx;
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

/*
	Assigns the west texture according to the angle facing
	and assigns the opposite texture (east) fliped horizontally
	and assigns the door texture for vertical lines on 2d space
*/
void	texture_we(t_vars *vars, t_ray *ray, t_render *render, t_pixel *tex)
{
	render->tx = (int)(ray->ry) % MAP_S;
	if (ray->ra > D90 && ray->ra < D270)
	{
		render->tx = (MAP_S - 1) - render->tx;
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
