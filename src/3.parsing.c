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

void	open_map_file(t_vars *vars, char *file)
{
	int		i;
	int		fd;
	char	buf[1000];
	char	**array;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		quit(vars, "File not found");
	i = read(fd, buf, 1000);
	buf[i] = '\0';
	// printf("%s\n", buf);
	array = ft_split(buf, '\n');
	i = -1;
	while (array[++i])
	{
		// printf("array[%d]: %s\n", i, array[i]);
		if (!ft_strncmp(array[i], "\r", 1))
			;
		else if (!ft_strncmp(array[i], "NO ", 3))
			vars->mapdata.north_texture = mlx_xpm_file_to_image(vars->mlx, ft_strtrim(ft_strchr(array[i], '.'), "\r"), &vars->mapdata.mlx_size, &vars->mapdata.mlx_size);
		else if (!ft_strncmp(array[i], "SO ", 3))
			vars->mapdata.south_texture = mlx_xpm_file_to_image(vars->mlx, ft_strtrim(ft_strchr(array[i], '.'), "\r"), &vars->mapdata.mlx_size, &vars->mapdata.mlx_size);
		else if (!ft_strncmp(array[i], "WE ", 3))
			vars->mapdata.west_texture = mlx_xpm_file_to_image(vars->mlx, ft_strtrim(ft_strchr(array[i], '.'), "\r"), &vars->mapdata.mlx_size, &vars->mapdata.mlx_size);
		else if (!ft_strncmp(array[i], "EA ", 3))
			vars->mapdata.east_texture = mlx_xpm_file_to_image(vars->mlx, ft_strtrim(ft_strchr(array[i], '.'), "\r"), &vars->mapdata.mlx_size, &vars->mapdata.mlx_size);
		else if (!ft_strncmp(array[i], "DO ", 3))
			vars->mapdata.door_texture = mlx_xpm_file_to_image(vars->mlx, ft_strtrim(ft_strchr(array[i], '.'), "\r"), &vars->mapdata.mlx_size, &vars->mapdata.mlx_size);
		else if (!ft_strncmp(array[i], "F ", 2))
		{
			vars->mapdata.floor_color[0] = ft_atoi(&array[i][2]);
			vars->mapdata.floor_color[1] = ft_atoi(ft_strchr(&array[i][2], ',') + 1);
			vars->mapdata.floor_color[2] = ft_atoi(ft_strchr(ft_strchr(&array[i][2], ',') + 1, ',') + 1);
		}
		else if (!ft_strncmp(array[i], "C ", 2))
		{
			vars->mapdata.ceiling_color[0] = ft_atoi(&array[i][2]);
			vars->mapdata.ceiling_color[1] = ft_atoi(ft_strchr(&array[i][2], ',') + 1);
			vars->mapdata.ceiling_color[2] = ft_atoi(ft_strchr(ft_strchr(&array[i][2], ',') + 1, ',') + 1);
		}
		else if (!ft_strncmp(array[i], "1", 1))
		{
			int	j;

			j = i;
			while (array[j])
				j++;
			// printf("j: %d\n", (j - i + 1));
			vars->mapdata.map = malloc(sizeof(char **) * (j - i + 1));
			j = -1;
			while (array[i])
				vars->mapdata.map[++j] = ft_strtrim(array[i++], "\r");
			// vars->mapdata.map[++j] = NULL;
			for (int x = 0; vars->mapdata.map[x]; x++)
				printf("%s\n", vars->mapdata.map[x]);
			handle_map(vars, vars->mapdata.map);
			break ;
		}
		else
		{
			quit(vars, "");
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

	y = 0;
	x = -1;
	while (map[y][++x])
	{
		if (map[y][x] != '1' && map[y][x] != '\r')
			quit(vars, "Map top not closed");
	}
	while (map[++y])
	{
		if (map[y][0] != '1' || map[y][ft_strlen(map[y]) - 1] != '1')
			quit(vars, "Map sides not closed");
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
				&& map[y][x] != 'N' && map[y][x] != 'S'
				&& map[y][x] != 'E' && map[y][x] != 'W')
				quit(vars, "Invalid character in map");
		}
		if (map[y + 1] == NULL)
			break ;
	}
	x = -1;
	while (map[y][++x])
	{
		if (map[y][x] != '1')
			quit(vars, "map bottom not closed");
	}
	// printf("%d\n", x);
	// printf("%d\n", y);
	// vars->mapdata.x = x;
	// vars->mapdata.y = y;
}
