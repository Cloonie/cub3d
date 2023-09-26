/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.parasing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:23:42 by mliew             #+#    #+#             */
/*   Updated: 2023/09/11 15:23:42 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_map(t_vars *vars, char **array);

void	unvalid_texture_file(t_vars *vars)
{
	if (vars->mapdata.north_texture == 0)
		quit(vars, "north_texture");
	if (vars->mapdata.south_texture == 0)
		quit(vars, "south_texture");
	if (vars->mapdata.east_texture == 0)
		quit(vars, "east_texture");
	if (vars->mapdata.west_texture == 0)
		quit(vars, "west_texture");
	if (vars->mapdata.door_texture == 0)
		quit(vars, "door_texture");
}

void	spawn_direction(t_vars *vars)
{
	if (vars->pspawn_dir == 'N')
		vars->pa = D270; // N
	else if (vars->pspawn_dir == 'S')
		vars->pa = PI/2; // S
	else if (vars->pspawn_dir == 'E')
		vars->pa = 0; // E
	else if (vars->pspawn_dir == 'W')
		vars->pa = PI; // W
	else
		quit(vars, "Spawn direction");
}

int	check_texture(t_vars *vars, char *str)
{
	int	s;

	s = vars->mapdata.mlx_size;
	if (!ft_strncmp(str, "NO ", 3))
		vars->mapdata.north_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strtrim(ft_strchr(str, '.'), "\r"), &s, &s);
	else if (!ft_strncmp(str, "SO ", 3))
		vars->mapdata.south_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strtrim(ft_strchr(str, '.'), "\r"), &s, &s);
	else if (!ft_strncmp(str, "WE ", 3))
		vars->mapdata.west_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strtrim(ft_strchr(str, '.'), "\r"), &s, &s);
	else if (!ft_strncmp(str, "EA ", 3))
		vars->mapdata.east_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strtrim(ft_strchr(str, '.'), "\r"), &s, &s);
	else if (!ft_strncmp(str, "DO ", 3))
		vars->mapdata.door_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strtrim(ft_strchr(str, '.'), "\r"), &s, &s);
	else
		return (1);
	return (0);
}

int	check_floor_ceiling_color(t_vars *vars, char *str)
{
	if (!ft_strncmp(str, "F ", 2))
	{
		vars->mapdata.floor_color[0] = ft_atoi(&str[2]);
		vars->mapdata.floor_color[1] = ft_atoi(ft_strchr(&str[2], ',') + 1);
		vars->mapdata.floor_color[2] = ft_atoi
			(ft_strchr(ft_strchr(&str[2], ',') + 1, ',') + 1);
	}
	else if (!ft_strncmp(str, "C ", 2))
	{
		vars->mapdata.ceiling_color[0] = ft_atoi(&str[2]);
		vars->mapdata.ceiling_color[1] = ft_atoi(ft_strchr(&str[2], ',') + 1);
		vars->mapdata.ceiling_color[2] = ft_atoi
			(ft_strchr(ft_strchr(&str[2], ',') + 1, ',') + 1);
	}
	else
		return (1);
	return (0);
}

// printf("%s\n", buf);
char	**open_file(t_vars *vars, char *file)
{
	int		i;
	int		fd;
	char	**array;
	char	buf[1000];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		quit(vars, "File not found");
	i = read(fd, buf, 1000);
	buf[i] = '\0';
	array = ft_split(buf, '\n');
	return (array);
}

void	parsing(t_vars *vars, char *file)
{
	int		i;
	char	**array;

	array = open_file(vars, file);
	i = -1;
	while (array[++i])
	{
		// printf("array[%d]: %s\n", i, array[i]);
		if (!ft_strncmp(array[i], "\r", 1))
			;
		else if (check_texture(vars, array[i]) == 0)
			;
		else if (check_floor_ceiling_color(vars, array[i]) == 0)
			;
		else if (!ft_strncmp(array[i], " ", 1) || !ft_strncmp(array[i], "1", 1))
		{
			int	j;
			j = i;
			while (array[j])
				j++;
			printf("j: %d\n", (j - i + 1));
			vars->mapdata.y = j - i;
			vars->mapdata.map = malloc(sizeof(char **) * (j - i + 1));
			j = -1;
			while (array[i])
				vars->mapdata.map[++j] = ft_strdup(array[i++]);
			vars->mapdata.map[++j] = NULL;
			for (int x = 0; vars->mapdata.map[x]; x++)
				printf("%s\n", vars->mapdata.map[x]);
			// printf("yyyy: %d\n", vars->mapdata.y);
			handle_map(vars, vars->mapdata.map);
			break ;
		}
		else
		{
			quit(vars, "Else Error");
			break ;
		}
	}
	unvalid_texture_file(vars);
	spawn_direction(vars);
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	handle_map(t_vars *vars, char **map)
{
	int	y;
	int	x;

	vars->mapdata.x = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == ' ' || map[y][x] == '\r')
			{
				if (map[y][x + 1])
					if (map[y][x + 1] != '1' && map[y][x + 1] != ' ' && map[y][x + 1] != '\r')
						printf("1map[y:%d][x:%d]\n", y, x);
				if (map[y + 1] && map[y + 1][x])
					if (map[y + 1][x] != '1' && map[y + 1][x] != ' ' && map[y + 1][x] != '\r')
						printf("2map[y:%d][x:%d]\n", y, x);
				if (x - 1 > 0)
					if (map[y][x - 1] != '1' && map[y][x - 1] != ' ' && map[y][x - 1] != '\r')
						printf("3map[y:%d][x:%d]\n", y, x);
				if (y - 1 > 0 && map[y - 1][x])
					if (map[y - 1][x] != '1' && map[y - 1][x] != ' ' && map[y - 1][x] != '\r')
						printf("4map[y:%d][x:%d]\n", y, x);
				if (map[y + 1] && map[y][x + 1])
					if (map[y + 1][x + 1] != '1' && map[y + 1][x + 1] != ' ' && map[y + 1][x + 1] != '\r')
						printf("5map[y:%d][x:%d]\n", y, x);
				if (map[y + 1] && x - 1 > 0 && map[y + 1][x - 1])
					if (map[y + 1][x - 1] != '1' && map[y + 1][x - 1] != ' ' && map[y + 1][x - 1] != '\r')
						printf("6map[y:%d][x:%d]\n", y, x);
				if (y - 1 > 0 && map[y - 1][x + 1])
					if (map[y - 1][x + 1] != '1' && map[y - 1][x + 1] != ' ' && map[y - 1][x + 1] != '\r')
						printf("7map[y:%d][x:%d]\n", y, x);
				if (y - 1 > 0 && x - 1 > 0 && map[y - 1][x - 1])
					if (map[y - 1][x - 1] != '1' && map[y - 1][x - 1] != ' ' && map[y - 1][x - 1] != '\r')
						printf("8map[y:%d][x:%d]\n", y, x);

				// {
				// 	printf("map[y:%d][x:%d]\n", y, x);
				// 	quit(vars, "No walls surrounding empty space.");
				// }
			}
		}
	}
	y = 0;
	x = -1;
	while (map[y][++x])
	{
		if (map[y][x] != '1' && map[y][x] != ' ' && map[y][x] != '\r')
			quit(vars, "Map top not closed");
	}
	while (map[++y])
	{
		if (map[y + 1] == NULL)
			break ;
		x = -1;
		while (map[y][++x] == ' ')
			;
		// if (map[y][0] != '1' || map[y][ft_strlen(map[y]) - 1] != '1')
		// 	quit(vars, "Map sides not closed");
		x = -1;
		while (map[y][++x])
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
				vars->px = (x * mapS) + (mapS / 2);
				vars->py = (y * mapS) + (mapS / 2);
				map[y][x] = '0';
			}
			else if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != '2'
				&& map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != '\r'
				&& map[y][x] != 'E' && map[y][x] != 'W' && map[y][x] != ' ')
				quit(vars, "Invalid character in map");
			if (x > vars->mapdata.x)
				vars->mapdata.x = x;
		}
	}
	x = -1;
	while (map[y][++x])
	{
		if (map[y][x] != '1' && map[y][x] != ' ')
			quit(vars, "map bottom not closed");
	}
	printf("x: %d\n", vars->mapdata.x);
	printf("y: %d\n", vars->mapdata.y);
	vars->map_size = 64;
	vars->win_height = vars->map_size * vars->mapdata.y;
	vars->win_width = vars->map_size * vars->mapdata.x;
}
