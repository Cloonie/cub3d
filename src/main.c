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

#include "../mlx_linux/mlx.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	(void)mlx_win;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "cub3d");
	mlx_loop(mlx);
}
