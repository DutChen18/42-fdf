/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:56:53 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/28 16:21:04 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <limits.h>

static int
	loop_hook(t_fdf *fdf)
{
	int		tmp;

	img_clear(fdf, vec_new(0, 0, 0, 0));
	fdf_render(fdf);
	tmp = mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	fdf_assert(tmp, "mlx_put_image_to_window");
	return (0);
}

static void
	init_fdf(t_fdf *fdf)
{
	int	bpp;
	int	size;
	int	endian;

	fdf->mlx = mlx_init();
	fdf_assert(fdf->mlx != NULL, "mlx_init");
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_width, fdf->win_height, "FdF");
	fdf_assert(fdf->win != NULL, "mlx_new_window");
	fdf->img = mlx_new_image(fdf->mlx, fdf->win_width, fdf->win_height);
	fdf_assert(fdf->img != NULL, "mlx_new_image");
	fdf->color = mlx_get_data_addr(fdf->img, &bpp, &size, &endian);
	fdf_assert(fdf->color != NULL, "mlx_get_data_addr");
	fdf->depth = malloc(fdf->win_width * fdf->win_height * sizeof(*fdf->depth));
	fdf_assert(fdf->depth != NULL, "malloc");
}

static void
	init_hooks(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, loop_hook, fdf);
	mlx_hook(fdf->win, 2, 0, key_down_hook, fdf);
	mlx_hook(fdf->win, 3, 0, key_up_hook, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_down_hook, fdf);
	mlx_hook(fdf->win, 5, 0, mouse_up_hook, fdf);
	mlx_hook(fdf->win, 6, 0, mouse_moved_hook, fdf);
	mlx_hook(fdf->win, 17, 0, close_hook, fdf);
}

static void
	init_props(t_fdf *fdf)
{
	size_t	i;

	fdf->min = INT_MAX;
	fdf->max = INT_MIN;
	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		if (fdf->map[i].height < fdf->min)
			fdf->min = fdf->map[i].height;
		if (fdf->map[i].height > fdf->max)
			fdf->max = fdf->map[i].height;
		i += 1;
	}
}

int
	main(int argc, char **argv)
{
	t_fdf	fdf;
	float	map_scale;

	fdf_assert(argc == 2, "argc");
	fdf.win_width = 1280;
	fdf.win_height = 960;
	init_fdf(&fdf);
	fdf.map = fdf_read(&fdf.map_width, &fdf.map_height, argv[1]);
	init_props(&fdf);
	map_scale = 2.0 / (fdf.map_width + fdf.map_height + fdf.max - fdf.min);
	fdf.translate = vec_new(0, 0, 0, 0);
	fdf.scale = vec_new(map_scale, map_scale, map_scale, 1);
	fdf.rotate = vec_new(M_PI / 4, M_PI / 4, 0, 0);
	fdf.mouse_1_down = 0;
	fdf.mouse_2_down = 0;
	fdf.use_persp = 0;
	fdf.use_fog = 0;
	fdf.color_mode = 0;
	fdf.draw_mode = 0;
	init_hooks(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
