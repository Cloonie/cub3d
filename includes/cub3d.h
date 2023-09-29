/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:37:51 by mliew             #+#    #+#             */
/*   Updated: 2023/09/29 17:14:19 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>

// unlock mac keyboard key hold down press //
// defaults write NSGlobalDomain ApplePressAndHoldEnabled -bool false

# ifdef __APPLE__
// key_hook keycodes for mac //
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define LEFT 123
#  define RIGHT 124
#  define SHIFT 257
#  define E 14
#  define M 46

# else

// key_hook keycodes for windows //
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define LEFT 65361
#  define RIGHT 65363
#  define SHIFT 65505
#  define E 101
#  define M 109
# endif

// variables

# define MAX_READ 1000
# define mapS 64
# define textureS 64

# define D0			6.28318530718
# define D90		1.57079632679
# define D180_PI	3.14159265359
# define D270		4.71238898038
# define DR			0.0174533

# define RUN_SPEED 2
# define ROTATION_SPEED 3

typedef struct s_mapdata
{
	void	*north_texture;
	void	*south_texture;
	void	*west_texture;
	void	*east_texture;
	void	*door_texture;
	int		mlx_size;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
	int		y;
	int		x;
}				t_mapdata;

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	shift;
	int	e;
	int	m;
}				t_key;

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
	float	shade;
	int		hd;
	int		vd;
}				t_ray;

typedef struct s_render
{
	float	ca;
	float	lineH;
	float	ty_step;
	float	ty_off;
	float	lineO;
	float	ty;
	float	tx;
}				t_render;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	int			map_size;
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
	int			pspawn_dir;
	int			player_size;
	void		*img;
	t_mapdata	mapdata;
	t_key		key;
	t_ray		ray;
	t_render	render;
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
	int		r;
	int		g;
	int		b;
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

// main.c

void	init_after_parsing(t_vars *vars);
void	start_init(t_vars *vars, char *file);
int		put_whole_image(t_vars *vars);

// key.c

void	open_close_door(t_vars *vars);
int		key_press(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);

// movement.c

void	rotation(t_vars *vars);
void	up_down(t_vars *vars, char **map, int xo, int yo);
void	left_right(t_vars *vars, char **map);
void	movement(t_vars *vars, char **map, int xo, int yo);

// parsing.c

char	**open_file(t_vars *vars, char *file);
void	create_map(t_vars *vars, char **array, int i);
void	parsing_loop(t_vars *vars, char **array);
void	parsing(t_vars *vars, char *file);

// parsing2.c

void	assign_dir(t_vars *vars, float pa, float pdx, float pdy);
void	spawn_direction(t_vars *vars);
int		init_texture(t_vars *vars, char *str);
void	unvalid_texture_file(t_vars *vars);
int		init_floor_ceiling_color(t_vars *vars, char *str);

// parsing3_map.c

void	handle_map(t_vars *vars, char **map, int x, int y);
void	handle_spaces(t_vars *vars, char **map, int y, int x);
void	spaces_diagonal(t_vars *vars, char **map, int y, int x);
void	handle_spawn(t_vars *vars, char **map, int y, int x);
void	check_walls(t_vars *vars, char **map, int y, int x);

// color.c

void	hex_to_rgb(int hex_color, int *red, int *green, int *blue);
int		rgb_to_hex(int red, int green, int blue);

// drawing.c

void	draw_pixel(t_vars *vars, int x, int y, int color);
void	draw_player(t_vars *vars);
void	draw_bg(t_vars *vars);
t_line	set_line(int x0, int y0, int x1, int y1);
void	draw_line(t_vars *vars, t_line *line, int color);

// raycasting.c

void	init_rays(t_vars *vars, t_ray *ray);
void	horizon_rays(t_vars *vars, t_ray *ray);
void	horizon_dof(t_vars *vars, t_ray *ray);
void	vertical_rays(t_vars *vars, t_ray *ray);
void	vertical_dof(t_vars *vars, t_ray *ray);

// raycasting2.c

void	get_nearest_ray(t_vars *vars, t_ray *ray);
void	raycasting(t_vars *vars);
void	draw_rays(t_vars *vars);

// rendering.c

void	render_ceiling(t_vars *vars, t_ray *ray, t_render *render);
void	render_floor(t_vars *vars, t_ray *ray, t_render *render);
void	texture_ns(t_vars *vars, t_ray *ray, t_render *render, t_pixel *tex);
void	texture_we(t_vars *vars, t_ray *ray, t_render *render, t_pixel *tex);

// rendering2.c

void	render_walls(t_vars *vars, t_ray *ray, t_render *render);
void	rendering(t_vars *vars, t_ray *ray);

// utils.c

void	quit(t_vars *vars, char *msg);
int		window_close(t_vars *vars);
float	dist(float ax, float ay, float bx, float by);

#endif