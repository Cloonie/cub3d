/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:37:51 by mliew             #+#    #+#             */
/*   Updated: 2023/09/11 19:36:09 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>

// unlock mac keyboard key hold down press //
// defaults write NSGlobalDomain ApplePressAndHoldEnabled -bool false

// key_hook keycodes for mac //
// # define ESC 53
// # define W 13
// # define A 0
// # define S 1
// # define D 2
// # define LEFT 123
// # define RIGHT 124

// key_hook keycodes for windows //
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

// variables
# define mapS 64
# define mapX 8
# define mapY 8
# define screenWidth (mapX*mapS)*3
# define screenHeight (mapY*mapS)*1.5
# define PI 3.14159265359
# define P2 PI/2		// 90 degrees
# define P3 3*PI/2		// 270 degrees
# define DR 0.0174533	// one degree in radians

static int map[mapY][mapX]=
{
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,1},
	{1,0,0,1,0,1,0,1},
	{1,0,0,0,0,1,0,1},
	{1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1},
};

typedef struct s_config
{
	char	north_texture[999];
	char	south_texture[999];
	char	west_texture[999];
	char	east_texture[999];
	int		floor_color[3];
	int		ceiling_color[3];
	int		map[mapX][mapY];
}				t_config;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
	int		player_size;
	void	*img;
}				t_vars;

typedef struct s_pixel
{
	char	*addr;
	int		pos;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		red;
	int		green;
	int		blue;
	int		alpha;
}				t_pixel;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	curr_x;
	int	curr_y;
	int	colour;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
}				t_line;

typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;

	float	hdis;
	float	hx;
	float	hy;
	float	a_tan;

	float	vdis;
	float	vx;
	float	vy;
	float	n_tan;

	float	tdis;
	int		colour;
}				t_ray;

// init.c

void	start_init(t_vars	*vars, t_config *config);
void	put_whole_image(t_vars *vars);

// movement.c

int		key_hook(int keycode, t_vars *vars);

// drawing.c

void	set_colour(t_pixel *pixel, int color);
void	draw_player(t_vars *vars);
void	draw_bg(t_vars *vars);
t_line	set_line(int x0, int y0, int x1, int y1);
void	draw_line(t_vars *vars, t_line *line, int colour);

// raycasting.c

void	draw_rays(t_vars *vars);

// utils.c

int		window_close(t_vars *vars);
float	dist(float ax, float ay, float bx, float by);

#endif