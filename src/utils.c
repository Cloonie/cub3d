/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:59:28 by mliew             #+#    #+#             */
/*   Updated: 2023/09/11 18:59:28 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	quit(t_vars *vars, char *msg)
{
	int	i;

	i = -1;
	while (vars->mapdata.map[++i])
		free(vars->mapdata.map[i]);
	free(vars->mapdata.map);
	printf("Error\n");
	perror(msg);
	exit(1);
}

int	window_close(t_vars *vars)
{
	quit(vars, "Window closed: close window button.\n");
	return (0);
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
