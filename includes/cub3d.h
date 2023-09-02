/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:37:51 by mliew             #+#    #+#             */
/*   Updated: 2023/09/03 02:12:35 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>

// key_hook keycodes for mac
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

#define chunkSize 100
#define mapWidth 12
#define mapHeight 6
#define screenWidth mapWidth*chunkSize
#define screenHeight mapHeight*chunkSize

int worldMap[mapHeight][mapWidth]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,3,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,2,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
};

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		pos_x;
	int		pos_y;
	char	*map;
	int		map_x;
	int		map_y;
	int		chunk_size;
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