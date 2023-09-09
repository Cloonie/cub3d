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
			player.addr[player.pos] = 0x00;		// Blue
			player.addr[player.pos + 1] = 0xFF;	// Green
			player.addr[player.pos + 2] = 0x00;	// Red
			player.addr[player.pos + 3] = 0x00;	// Alpha
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
				bg.addr[pixel] = 0xFF;		// Blue
				bg.addr[pixel + 1] = 0xFF;	// Green
				bg.addr[pixel + 2] = 0xFF;	// Red
			}
			else if (map[y][x] == 2)
			{
				bg.addr[pixel] = 0xFF;		// Blue
				bg.addr[pixel + 1] = 0x00;	// Green
				bg.addr[pixel + 2] = 0x00;	// Red
			}
			else if (map[y][x] == 3)
			{
				bg.addr[pixel] = 0x00;		// Blue
				bg.addr[pixel + 1] = 0x00;	// Green
				bg.addr[pixel + 2] = 0xFF;	// Red
			}
			else
			{
				bg.addr[pixel] = 0x50;		// Blue
				bg.addr[pixel + 1] = 0x50;	// Green
				bg.addr[pixel + 2] = 0x50;	// Red
			}
		}
		bg.x = -1;
	}
}

void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int colour)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int err2;

	while (1)
	{
		mlx_pixel_put(vars->mlx, vars->win, x0, y0, colour);

		if (x0 == x1 && y0 == y1)
			break ;

		err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

float	dist(float ax, float ay, float bx, float by, float ang)
{
	(void)ang;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_rays(t_vars *vars)
{
	t_ray	ray;

	// init angle facing straight back by 30 radians to get fov
	ray.ra = vars->pa - (DR * 30);
	if (ray.ra < 0)
		ray.ra += 2 * PI;
	if (ray.ra > 2 * PI)
		ray.ra -= 2 * PI;

	// loop for each ray
	for (int r = 0; r < 240; r++)
	{
		// horizonal lines
		ray.dof = 0;
		ray.disH = 1000000;
		ray.hx = vars->px;
		ray.hy = vars->py;
		ray.aTan = -1/tan(ray.ra);
		if (ray.ra > PI) // looking up
		{
			ray.ry = (((int)vars->py >> 6) << 6) - 0.0001;
			ray.rx = (vars->py - ray.ry) * ray.aTan + vars->px;
			ray.yo = -64;
			ray.xo = -ray.yo * ray.aTan;
		}
		if (ray.ra < PI) // looking down
		{
			ray.ry = (((int)vars->py >> 6) << 6) + 64;
			ray.rx = (vars->py - ray.ry) * ray.aTan + vars->px;
			ray.yo = 64;
			ray.xo = -ray.yo * ray.aTan;
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
				ray.disH = dist(vars->px, vars->py, ray.hx, ray.hy, ray.ra);
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
		ray.disV = 1000000;
		ray.vx = vars->px;
		ray.vy = vars->py;
		ray.nTan = -tan(ray.ra);
		if (ray.ra > P2 && ray.ra < P3) // looking left
		{
			ray.rx = (((int)vars->px >> 6) << 6) - 0.0001;
			ray.ry = (vars->px - ray.rx) * ray.nTan + vars->py;
			ray.xo = -64;
			ray.yo = -ray.xo * ray.nTan;
		}
		if (ray.ra < P2 || ray.ra > P3) // looking right
		{
			ray.rx = (((int)vars->px >> 6) << 6) + 64;
			ray.ry = (vars->px - ray.rx) * ray.nTan + vars->py;
			ray.xo = 64;
			ray.yo = -ray.xo * ray.nTan;
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
				ray.disV = dist(vars->px, vars->py, ray.vx, ray.vy, ray.ra);
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
		if (ray.disV < ray.disH)
		{
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.disT = ray.disV;
			colour = 0xFF0000;
		}
		if (ray.disH < ray.disV)
		{
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.disT = ray.disH;
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
		ray.disT = ray.disT*cos(ca);
		float lineH = (mapS*440)/ray.disT;
		if (lineH > 440)
			lineH = 440;
		float lineO = 240-lineH/2;
		for (int d = 0; d < 2; d++)
			draw_line(vars, r*2+d+(screenWidth/2)+16, lineO, r*2+d+(screenWidth/2)+16, lineH+lineO, colour);

		// loop for each ray at next radian
		ray.ra += DR/4;
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
	if (keycode == A)
	{
		if (vars->pa < 0)
			vars->pa += 2 * PI;
		vars->pa -= 0.1;
		vars->pdx = cos(vars->pa) * 10;
		vars->pdy = sin(vars->pa) * 10;
	}
	if (keycode == D)
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

int	main(void)
{
	t_vars	vars;

	init(&vars);
	print_img(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}

// mlx_loop_hook(vars.mlx, loop_hook, &vars);
// int	loop_hook(int keycode, t_vars *vars)
// {
// 	(void)keycode;
// 	(void)vars;
// 	return (0);
// }