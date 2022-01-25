/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:56:53 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/25 11:42:44 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int
	loop_hook(t_fdf *fdf)
{
	int	tmp;

	img_clear(fdf, 0);
	fdf_update(fdf);
	fdf_render(fdf);
	tmp = mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	fdf_assert(tmp, "mlx_put_image_to_window");
	return (0);
}

int
	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53 || keycode == 12)
		exit(EXIT_SUCCESS);
	if (keycode == 35)
		fdf->projection = !fdf->projection;
	return (0);
}

int
	close_hook(t_fdf *fdf)
{
	(void) fdf;
	exit(EXIT_SUCCESS);
	return (0);
}

int
	main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf_assert(argc == 2, "argc");
	fdf.win_width = 1280;
	fdf.win_height = 960;
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, fdf.win_width, fdf.win_height, "FdF");
	fdf.img = mlx_new_image(fdf.mlx, fdf.win_width, fdf.win_height);
	fdf.map = fdf_read(&fdf.map_width, &fdf.map_height, argv[1]);
	fdf.translate_x = 0;
	fdf.translate_y = 0;
	fdf.scale = 1;
	fdf.rot_x = M_PI / 4;
	fdf.rot_y = M_PI / 4;
	fdf.mouse_left_down = 0;
	fdf.mouse_right_down = 0;
	fdf.projection = 0;
	mlx_loop_hook(fdf.mlx, loop_hook, &fdf);
	mlx_key_hook(fdf.win, key_hook, &fdf);
	mlx_hook(fdf.win, 4, 0, mouse_down_hook, &fdf);
	mlx_hook(fdf.win, 5, 0, mouse_up_hook, &fdf);
	mlx_hook(fdf.win, 6, 0, mouse_moved_hook, &fdf);
	mlx_hook(fdf.win, 17, 0, close_hook, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
