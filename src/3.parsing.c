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

#include "../includes/cub3d.h"

void	open_map_file(t_mapdata *mapdata)
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
		printf("array[%d]: %s\n", i, array[i]);
		if (!ft_strncmp(array[i], "NO ", 3))
			mapdata->north_texture = ft_strchr(array[i], '.');
		else if (!ft_strncmp(array[i], "SO ", 3))
			mapdata->south_texture = ft_strchr(array[i], '.');
		else if (!ft_strncmp(array[i], "WE ", 3))
			mapdata->west_texture = ft_strchr(array[i], '.');
		else if (!ft_strncmp(array[i], "EA ", 3))
			mapdata->east_texture = ft_strchr(array[i], '.');
		else if (!ft_strncmp(array[i], "F ", 2))
		{
			mapdata->floor_color[0] = ft_atoi(&array[i][2]);
			mapdata->floor_color[1] = ft_atoi(ft_strchr(&array[i][2], ',') + 1);
			mapdata->floor_color[2] = ft_atoi(ft_strchr(ft_strchr(&array[i][2], ',') + 1, ',') + 1);
		}
		else if (!ft_strncmp(array[i], "C ", 2))
		{
			mapdata->ceiling_color[0] = ft_atoi(&array[i][2]);
			mapdata->ceiling_color[1] = ft_atoi(ft_strchr(&array[i][2], ',') + 1);
			mapdata->ceiling_color[2] = ft_atoi(ft_strchr(ft_strchr(&array[i][2], ',') + 1, ',') + 1);
		}
	}
}

