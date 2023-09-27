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
	buf[i] = '\r';
	buf[i + 1] = '\0';
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
		if (!ft_strncmp(array[i], "\r", 1)
			|| init_texture(vars, array[i]) == 0
			|| init_floor_ceiling_color(vars, array[i]) == 0)
			;
		else if (!ft_strncmp(array[i], " ", 1) || !ft_strncmp(array[i], "1", 1))
		{
			create_map(vars, array, i);
			handle_map(vars, vars->mapdata.map);
			break ;
		}
		else
			quit(vars, "Invalid Colour for floor / ceiling");
	}
	if (vars->mapdata.map == 0)
		quit (vars, "Map not found");
	unvalid_texture_file(vars);
	spawn_direction(vars);
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
