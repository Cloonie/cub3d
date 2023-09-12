/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:33:43 by mliew             #+#    #+#             */
/*   Updated: 2023/08/28 14:33:43 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(void)
{
	t_vars		vars;
	t_mapdata	config;

	start_init(&vars, &config);
	put_whole_image(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, window_close, &vars);
	mlx_loop(vars.mlx);
}
