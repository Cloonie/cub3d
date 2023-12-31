/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.parsing2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:55:18 by mliew             #+#    #+#             */
/*   Updated: 2023/09/27 15:55:18 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_dir(t_vars *vars, float pa, float pdx, float pdy)
{
	vars->pa = pa;
	vars->pdx = pdx;
	vars->pdy = pdy;
}

/*
	Degrees
	0		East
	90		South
	180		West
	270		North
*/
void	spawn_direction(t_vars *vars)
{
	if (vars->pspawn_dir == 'N')
		assign_dir(vars, D270, 0, -1);
	else if (vars->pspawn_dir == 'S')
		assign_dir(vars, D90, 0, 1);
	else if (vars->pspawn_dir == 'E')
		assign_dir(vars, 0, 1, 0);
	else if (vars->pspawn_dir == 'W')
		assign_dir(vars, D180_PI, -1, 0);
	else
		quit(vars, "Spawn direction");
}

int	init_texture(t_vars *vars, char *str)
{
	int		s;
	char	*tmp;

	s = vars->mapdata.mlx_size;
	tmp = str;
	tmp[ft_strlen(tmp) - 1] = 0;
	if (!ft_strncmp(str, "NO ", 3))
		vars->mapdata.north_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strchr(tmp, '.'), &s, &s);
	else if (!ft_strncmp(str, "SO ", 3))
		vars->mapdata.south_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strchr(tmp, '.'), &s, &s);
	else if (!ft_strncmp(str, "WE ", 3))
		vars->mapdata.west_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strchr(tmp, '.'), &s, &s);
	else if (!ft_strncmp(str, "EA ", 3))
		vars->mapdata.east_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strchr(tmp, '.'), &s, &s);
	else if (!ft_strncmp(str, "DO ", 3))
		vars->mapdata.door_texture = mlx_xpm_file_to_image(vars->mlx,
				ft_strchr(tmp, '.'), &s, &s);
	else
		return (1);
	return (0);
}

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

int	init_floor_ceiling_color(t_vars *vars, char *str)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (str[++i])
		if (str[i] == ',')
			comma++;
	if (!ft_strncmp(str, "F ", 2) && comma == 2)
	{
		vars->mapdata.floor_color[0] = ft_atoi(&str[2]);
		vars->mapdata.floor_color[1] = ft_atoi(ft_strchr(&str[2], ',') + 1);
		vars->mapdata.floor_color[2] = ft_atoi
			(ft_strchr(ft_strchr(&str[2], ',') + 1, ',') + 1);
		for (int x = 0; x < 3; x++)
		{
			if (vars->mapdata.floor_color[x] < 0 || vars->mapdata.floor_color[x] > 255)
				quit(vars, "COLOR FLOOR ERROR");
		}
	}
	else if (!ft_strncmp(str, "C ", 2) && comma == 2)
	{
		vars->mapdata.ceiling_color[0] = ft_atoi(&str[2]);
		vars->mapdata.ceiling_color[1] = ft_atoi(ft_strchr(&str[2], ',') + 1);
		vars->mapdata.ceiling_color[2] = ft_atoi
			(ft_strchr(ft_strchr(&str[2], ',') + 1, ',') + 1);
		for (int x = 0; x < 3; x++)
		{
			if (vars->mapdata.ceiling_color[x] < 0 || vars->mapdata.ceiling_color[x] > 255)
				quit(vars, "COLOR CEILING ERROR");
		}
	}
	else
		return (1);
	return (0);
}
