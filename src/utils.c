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
	printf("Error\n");
	perror(msg);
	exit(1);
}

int	window_close(t_vars *vars)
{
	(void)vars;
	printf("Window closed: close window button.\n");
	exit(0);
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
