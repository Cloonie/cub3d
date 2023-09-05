/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:37:51 by mliew             #+#    #+#             */
/*   Updated: 2023/09/05 15:07:52 by mliew            ###   ########.fr       */
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

#define chunkSize 100
#define mapWidth 12
#define mapHeight 6
#define screenWidth mapWidth*chunkSize
#define screenHeight mapHeight*chunkSize
#define PI 3.14159265359

int worldMap[mapHeight][mapWidth]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,0,3,0,2,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
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

#endif