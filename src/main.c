/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:33:43 by mliew             #+#    #+#             */
/*   Updated: 2023/08/28 14:33:43 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	After using mlx_get_data_addr to get the return value of an image address
	use this formula [pos = y * size_line + x * (bits_per_pixel / 8)] to get
	the position of that pixel using the address then apply colours or a pixel
	colour from another address from an xpm file.

	addr[pos] = 0x00;		Blue
	addr[pos + 1] = 0xFF;	Green
	addr[pos + 2] = 0x50;	Red
	addr[pos + 3] = 0x00;	Alpha
*/

void	draw_player(t_vars *vars)
{
	t_pixel	player;

	player.x = vars->px - (vars->player_size/2);
	player.y = vars->py - (vars->player_size/2);

	player.addr = mlx_get_data_addr(vars->img, &player.bits_per_pixel, &player.size_line, &player.endian);
	while (player.y < (vars->py + (vars->player_size/2)))
	{
		while (player.x < (vars->px + (vars->player_size/2)))
		{
			player.pos = player.y * player.size_line + player.x * (player.bits_per_pixel / 8);
			player.addr[player.pos] = 0x00;
			player.addr[player.pos + 1] = 0xFF;
			player.addr[player.pos + 2] = 0x00;
			player.x++;
		}
		player.x = vars->px - (vars->player_size/2);
		player.y++;
	}
}

void	draw_bg(t_vars *vars)
{
	t_pixel	bg;

	bg.addr = mlx_get_data_addr(vars->img, &bg.bits_per_pixel, &bg.size_line, &bg.endian);
	bg.x = -1;
	bg.y = -1;
	while (++bg.y < (mapY * mapS))
	{
		while (++bg.x < (mapX * mapS))
		{
			int pixel = bg.y * bg.size_line + bg.x * (bg.bits_per_pixel / 8);
			int x = bg.x/mapS;
			int y = bg.y/mapS;
			if (bg.y % mapS == 0 || bg.x % mapS == 0)
				;
			else if (map[y][x] == 1)
			{
				bg.addr[pixel] = 0xFF;
				bg.addr[pixel + 1] = 0xFF;
				bg.addr[pixel + 2] = 0xFF;
			}
			else if (map[y][x] == 2)
			{
				bg.addr[pixel] = 0xFF;
				bg.addr[pixel + 1] = 0x00;
				bg.addr[pixel + 2] = 0x00;
			}
			else if (map[y][x] == 3)
			{
				bg.addr[pixel] = 0x00;
				bg.addr[pixel + 1] = 0x00;
				bg.addr[pixel + 2] = 0xFF;
			}
			else
			{
				bg.addr[pixel] = 0x50;
				bg.addr[pixel + 1] = 0x50;
				bg.addr[pixel + 2] = 0x50;
			}
		}
		bg.x = -1;
	}
}

void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int colour)
{
	t_line	line;

	line.x0 = x0;
	line.y0 = y0;
	line.x1 = x1;
	line.y1 = y1;
	line.dx = abs(x1 - x0);
	line.dy = abs(y1 - y0);
	line.sx = (x0 < x1) ? 1 : -1;
	line.sy = (y0 < y1) ? 1 : -1;
	line.err = line.dx - line.dy;
	while (1)
	{
		mlx_pixel_put(vars->mlx, vars->win, line.x0, line.y0, colour);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		line.err2 = 2 * line.err;
		if (line.err2 > -line.dy)
		{
			line.err -= line.dy;
			line.x0 += line.sx;
		}
		if (line.err2 < line.dx)
		{
			line.err += line.dx;
			line.y0 += line.sy;
		}
	}
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_rays(t_vars *vars)
{
	t_ray	ray;

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
		ray.hdis = 1000000;
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
		ray.vdis = 1000000;
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
		int colour;
		if (ray.vdis < ray.hdis)
		{
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.tdis = ray.vdis;
			colour = 0xFF0000;
		}
		if (ray.hdis < ray.vdis)
		{
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.tdis = ray.hdis;
			colour = 0x990000;
		}
		// printf("vertical rx: %f ry: %f\n", ray.rx, ray.ry);
		draw_line(vars, vars->px, vars->py, ray.rx, ray.ry, colour);

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
			draw_line(vars, ray.r*2+d+(mapY*mapS)+16, lineO, ray.r*2+d+(mapY*mapS)+16, lineH+lineO, colour);

		// loop for each ray at next radian
		ray.ra += DR / 6;
		if (ray.ra < 0)
			ray.ra += 2 * PI;
		if (ray.ra > 2 * PI)
			ray.ra -= 2 * PI;
	}
}

void	print_img(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx, screenWidth, screenHeight);
	draw_bg(vars);
	draw_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	// int x1 = (vars->px + 5) + 25 * cos(vars->pa); // x endpoints cordinates
	// int y1 = (vars->py + 5) + 25 * sin(vars->pa); // y endpoints cordinates
	// draw_line(vars, x1, y1, 0x00FFFF);
	draw_rays(vars);
	mlx_destroy_image(vars->mlx, vars->img);
}

int	key_hook(int keycode, t_vars *vars)
{
	// printf("key_hook func keycode: %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == LEFT)
	{
		if (vars->pa < 0)
			vars->pa += 2 * PI;
		vars->pa -= 0.1;
		vars->pdx = cos(vars->pa) * 10;
		vars->pdy = sin(vars->pa) * 10;
	}
	if (keycode == RIGHT)
	{
		if (vars->pa > (2 * PI))
			vars->pa -= 2 * PI;
		vars->pa += 0.1;
		vars->pdx = cos(vars->pa) * 10;
		vars->pdy = sin(vars->pa) * 10;
	}
	if (keycode == W)
	{
		vars->px += vars->pdx;
		vars->py += vars->pdy;
	}
	if (keycode == S)
	{
		vars->px -= vars->pdx;
		vars->py -= vars->pdy;
	}
	if (keycode == A)
	{
		vars->px += cos(vars->pa - (PI / 2.0)) * 10;
		vars->py += sin(vars->pa - (PI / 2.0)) * 10;
	}
	if (keycode == D)
	{
		vars->px += cos(vars->pa + (PI / 2.0)) * 10;
		vars->py += sin(vars->pa + (PI / 2.0)) * 10;
	}
	print_img(vars);
	// printf("player x:%f y:%f\n", vars->px, vars->py);
	return (0);
	}

void	init(t_vars	*vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, screenWidth, screenHeight, "cub3d");
	vars->player_size = 10;
	vars->px = 100;
	vars->py = 100;
	vars->pa = 0;
	vars->pdx = cos(vars->pa) * 10;
	vars->pdy = sin(vars->pa) * 10;
}

int	window_close(t_vars *vars)
{
	(void)vars;
	printf("window close\n");
	exit(0);
}

int	main(void)
{
	t_vars	vars;

	init(&vars);
	print_img(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, window_close, &vars);
	mlx_loop(vars.mlx);
}

// mlx_loop_hook(vars.mlx, loop_hook, &vars);
// int	loop_hook(int keycode, t_vars *vars)
// {
// 	(void)keycode;
// 	(void)vars;
// 	return (0);
// }