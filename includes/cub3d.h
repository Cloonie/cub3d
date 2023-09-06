/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:37:51 by mliew             #+#    #+#             */
/*   Updated: 2023/09/06 13:57:16 by mliew            ###   ########.fr       */
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
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2

// key_hook keycodes for windows
// # define ESC 65307
// # define W 119
// # define A 97
// # define S 115
// # define D 100

#define chunkSize 64
#define mapX 7
#define mapY 7
#define screenWidth mapX*chunkSize
#define screenHeight mapY*chunkSize
#define PI 3.14159265359
#define P2 PI/2
#define P3 3*PI/2


int map[mapY][mapX]=
{
	{1,1,1,1,1,1,1},
	{1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1},
	{1,0,0,1,0,0,1},
	{1,1,0,0,0,1,1},
	{1,0,0,0,0,0,1},
	{1,1,1,1,1,1,1},
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
}				t_ray;

#endif