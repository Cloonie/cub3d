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

void	open_map_file(t_vars *vars)
{
	int		i;
	int		fd;
	char	buf[1000];
	char	**array;

	fd = open("maps/map.cub", O_RDONLY);
	if (fd == -1)
		perror("fd cant open");
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
			int j = -1;
			while (array[i][++j])
			{
				if (array[i][j] != '1' && array[i][j] != '\r')
					perror("map top not closed");
			}
			while (array[++i])
			{
				if (array[i][0] != '1' || array[i][ft_strlen(array[i]) - 2] != '1')
					perror("map sides not closed");
				// int player_found = 0;
				j = -1;
				// while (array[i][++j])
				// {
				// 	if (array[i][j] == 'N' || array[i][j] == 'S');
				// }
				if (array[i + 1] == NULL)
					break ;
			}
			j = -1;
			while (array[i][++j])
			{
				if (array[i][j] != '1')
					perror("map bottom not closed");
			}
		}
		else
		{
			perror("error");
			break ;
		}
	}
}

