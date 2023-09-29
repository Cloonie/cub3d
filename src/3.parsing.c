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
	char	buf[MAX_READ];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		quit(vars, "File not found");
	if (ft_strchr(file, '.') == NULL)
		quit(vars, "File doesn't have a [.]");
	if (ft_strncmp(ft_strchr(file, '.'), ".cub", 5))
		quit(vars, "File doesn't end with [.cub]");
	i = read(fd, buf, MAX_READ);
	buf[i] = '\r';
	buf[i + 1] = '\0';
	array = ft_split(buf, '\n');
	return (array);
}

// printf("j: %d\n", (j - i + 1));
// for (int x = 0; vars->mapdata.map[x]; x++)
// 	printf("map[%d] %s\n", x, vars->mapdata.map[x]);
void	create_map(t_vars *vars, char **array, int i)
{
	int	j;

	j = i;
	while (array[j])
		j++;
	vars->mapdata.y = j - i;
	vars->mapdata.map = malloc(sizeof(char **) * (j - i + 1));
	j = -1;
	while (array[i])
		vars->mapdata.map[++j] = ft_strdup(array[i++]);
	vars->mapdata.map[++j] = NULL;
	ft_strlcat(vars->mapdata.map[0], "\r\0", ft_strlen(vars->mapdata.map[0]) + 2);
}

// printf("array[%d]: %s\n", i, array[i]);
void	parsing_loop(t_vars *vars, char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (!ft_strncmp(array[i], "\r", 1)
			|| init_texture(vars, array[i]) == 0
			|| init_floor_ceiling_color(vars, array[i]) == 0)
			;
		else if (!ft_strncmp(array[i], " ", 1) || !ft_strncmp(array[i], "1", 1))
		{
			create_map(vars, array, i);
			handle_map(vars, vars->mapdata.map, -1, -1);
			break ;
		}
		else
			quit(vars, "Map first char / Color");
	}
}

void	parsing(t_vars *vars, char *file)
{
	int		i;
	char	**array;

	array = open_file(vars, file);
	parsing_loop(vars, array);
	if (vars->mapdata.map == 0)
		quit (vars, "Map not found");
	unvalid_texture_file(vars);
	spawn_direction(vars);
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
