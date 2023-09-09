/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:37:51 by mliew             #+#    #+#             */
/*   Updated: 2023/09/09 15:02:40 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

// key_hook keycodes for mac
// defaults write NSGlobalDomain ApplePressAndHoldEnabled -bool false
// # define ESC 53
// # define W 13
// # define A 0
// # define S 1
// # define D 2

// key_hook keycodes for windows
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100

# define mapS 64
# define mapX 8
# define mapY 8
# define screenWidth (mapX*mapS)*2
# define screenHeight mapY*mapS
# define PI 3.14159265359
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533 // one degree in radians

int map[mapY][mapX]=
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
}				t_pixel;

typedef struct s_ray
{
	int		r; // ray count
	int		mx; // map x
	int		my; // map y
	int		mp; // map point
	int		dof; // depth of field
	float	rx; // ray x
	float	ry; // ray y
	float	ra; // ray angle
	float	xo; // x offset
	float	yo; // y offset
	float	disH;
	float	hx;
	float	hy;
	float	aTan;
	float	disV;
	float	vx;
	float	vy;
	float	nTan;
	float	disT;
}				t_ray;

#endif