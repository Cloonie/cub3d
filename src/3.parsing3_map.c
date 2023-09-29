/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.parsing3_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:26:40 by mliew             #+#    #+#             */
/*   Updated: 2023/09/28 15:26:40 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_map(t_vars *vars, char **map, int x, int y)
{
	y = -1;
	while (map[++y])
	{
		if (!ft_strncmp(map[y], "\r", 1))
			quit(vars, "Empty line in between map");
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == ' ' || map[y][x] == '\r')
				handle_spaces(vars, map, y, x);
			handle_spawn(vars, map, y, x);
			if (x > vars->mapdata.x)
				vars->mapdata.x = x;
			if (map[y + 1] == NULL && map[y][x + 1] == 0)
			{
				if (x > vars->mapdata.x)
					vars->mapdata.x = x + 1;
				break ;
			}
		}
	}
	check_walls(vars, map, y, x);
	printf("map x: %d\n", vars->mapdata.x);
	printf("map y: %d\n", vars->mapdata.y);
}

// printf("1[x:%d] [y:%d]\n", x, y);
void	handle_spaces(t_vars *vars, char **map, int y, int x)
{
	if (map[y][x + 1])
		if (map[y][x + 1] != '1' && map[y][x + 1] != ' '
		&& map[y][x + 1] != '\r')
			quit(vars, "Map not fully closed horizonally/vertically");
	if (map[y + 1] && map[y + 1][x] && x < ft_strlen(map[y + 1]))
		if (map[y + 1][x] != '1' && map[y + 1][x] != ' '
		&& map[y + 1][x] != '\r')
			quit(vars, "Map not fully closed horizonally/vertically");
	if (x - 1 > 0)
		if (map[y][x - 1] != '1' && map[y][x - 1] != ' '
		&& map[y][x - 1] != '\r')
			quit(vars, "Map not fully closed horizonally/vertically");
	if (y - 1 > 0 && map[y - 1][x] && x < ft_strlen(map[y - 1]))
		if (map[y - 1][x] != '1' && map[y - 1][x] != ' '
		&& map[y - 1][x] != '\r')
			quit(vars, "Map not fully closed horizonally/vertically");
	spaces_diagonal(vars, map, y, x);
}

void	spaces_diagonal(t_vars *vars, char **map, int y, int x)
{
	if (map[y + 1] && map[y][x + 1] && map[y + 1][x + 1]
	&& x < ft_strlen(map[y + 1]))
		if (map[y + 1][x + 1] != '1' && map[y + 1][x + 1] != ' '
		&& map[y + 1][x + 1] != '\r')
			quit(vars, "Map not fully closed diagonally");
	if (map[y + 1] && map[y + 1][x - 1] && x - 1 > 0
		&& x < ft_strlen(map[y + 1]))
		if (map[y + 1][x - 1] != '1' && map[y + 1][x - 1] != ' '
		&& map[y + 1][x - 1] != '\r')
			quit(vars, "Map not fully closed diagonally");
	if (y - 1 > 0 && map[y - 1][x + 1] && x < ft_strlen(map[y - 1]))
		if (map[y - 1][x + 1] != '1' && map[y - 1][x + 1] != ' '
		&& map[y - 1][x + 1] != '\r')
			quit(vars, "Map not fully closed diagonally");
	if (y - 1 > 0 && x - 1 > 0 && x < ft_strlen(map[y - 1])
		&& map[y - 1][x - 1])
		if (map[y - 1][x - 1] != '1' && map[y - 1][x - 1] != ' '
		&& map[y - 1][x - 1] != '\r')
			quit(vars, "Map not fully closed diagonally");
}

void	handle_spawn(t_vars *vars, char **map, int y, int x)
{
	if (vars->pspawn_dir != 0
		&& (map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W'))
		quit(vars, "Multiple player spawn point");
	else if (vars->pspawn_dir == 0
		&& (map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W'))
	{
		vars->pspawn_dir = map[y][x];
		vars->px = (x * MAP_S) + (MAP_S / 2);
		vars->py = (y * MAP_S) + (MAP_S / 2);
		map[y][x] = '0';
	}
	else if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != '2'
		&& map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != '\r'
		&& map[y][x] != 'E' && map[y][x] != 'W' && map[y][x] != ' ')
	{
		printf("%c\n", map[y][x]);
		quit(vars, "Invalid character in map");
	}
}

/*
	check first string of map only chars allowed ('1', ' ', '\r')
	check last string of map only chars allowed ('1', ' ', '\r')
	check first char of each string of map only chars allowed ('1', ' ')
*/
void	check_walls(t_vars *vars, char **map, int y, int x)
{
	x = -1;
	while (map[0][++x])
	{
		if (map[0][x] != '1' && map[0][x] != ' ' && map[0][x] != '\r')
			quit(vars, "Map top not closed");
	}
	x = -1;
	while (map[vars->mapdata.y - 1][++x])
	{
		if (map[vars->mapdata.y - 1][x] != '1'
			&& map[vars->mapdata.y - 1][x] != ' '
			&& map[vars->mapdata.y - 1][x] != '\r')
			quit(vars, "map bottom not closed");
	}
	y = -1;
	while (map[++y] && map[y][0])
	{
		if (map[y][0] != '1' && map[y][0] != ' ' && map[y][0] != '\r')
			quit(vars, "map left side not closed");
	}
}
