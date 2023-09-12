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

	fd = open("maps/map.cub", O_RDONLY);
	if (fd == -1)
		perror("fd cant open");
	i = read(fd, buf, 1000);
	buf[i] = '\0';

	printf("%s\n", buf);

	char **array = ft_split(buf, '\n');
	i = -1;
	while (array[++i])
	{
		if (array[i])
			printf("array[%d]: %s\n", i, array[i]);
	}

	mapdata->north_texture = ft_strnstr(array[0], "./", 100);
	mapdata->south_texture = ft_strnstr(array[1], "./", 100);
	mapdata->west_texture = ft_strnstr(array[2], "./", 100);
	mapdata->east_texture = ft_strnstr(array[3], "./", 100);
}

