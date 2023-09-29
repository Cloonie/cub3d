/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.rendering2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:04:41 by mliew             #+#    #+#             */
/*   Updated: 2023/09/28 16:04:41 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_walls(t_vars *vars, t_ray *ray, t_render *render)
{
	t_pixel	tex;
	int		y;

	y = -1;
	render->ty = render->ty_off * render->ty_step;
	if (ray->shade == 1)
		texture_ns(vars, ray, render, &tex);
	else
		texture_we(vars, ray, render, &tex);
	while (++y < render->line_h)
	{
		tex.pos = (int)render->ty * tex.size_line + (int)render->tx
			* (tex.bits_per_pixel / 8);
		draw_pixel(vars, ray->r, (y + render->line_o),
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
	render->line_h = (MAP_S * vars->win_height) / ray->tdis;
	render->ty_step = MAP_S / (float)render->line_h;
	render->ty_off = 0;
	if (render->line_h > vars->win_height)
	{
		render->ty_off = (render->line_h - vars->win_height) / 2;
		render->line_h = vars->win_height;
	}
	render->line_o = (vars->win_height / 2) - (render->line_h / 2) - 1;
	render_ceiling(vars, ray, render);
	render_walls(vars, ray, render);
	render_floor(vars, ray, render);
}
