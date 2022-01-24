/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:56:53 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/24 16:14:47 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int
	loop_hook(t_fdf *fdf)
{
	fdf_update(fdf);
	fdf_render(fdf);
	return (0);
}

int
	key_hook(int keycode, t_fdf *fdf)
{
	(void) keycode;
	(void) fdf;
	exit(EXIT_SUCCESS);
	return (0);
}

int
	main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf_assert(argc == 2, "argc not 2");
	fdf.win_width = 1280;
	fdf.win_height = 960;
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, fdf.win_width, fdf.win_height, "FdF");
	fdf.img = mlx_new_image(fdf.mlx, fdf.win_width, fdf.win_height);
	fdf.map = fdf_read(&fdf.map_width, &fdf.map_height, argv[1]);
	mlx_loop_hook(fdf.mlx, loop_hook, &fdf);
	mlx_key_hook(fdf.win, key_hook, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
