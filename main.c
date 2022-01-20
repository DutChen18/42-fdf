/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 15:56:53 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/20 16:24:08 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

t_vec
	trans(t_vec vec, float time)
{
	t_mat	mat;

	mat = mat_ortho(
			vec_new(-4.0f, -3.0f, -1.0f, 0.0f),
			vec_new(0.0f, 0.0f, 1.0f, 0.0f));
	vec = mul_vm(vec, mat_rotate_z(time));
	vec = mul_vm(vec, mat_rotate_z(M_PI / 4));
	vec = mul_vm(vec, mat_rotate_x(M_PI / 4));
	vec = mul_vm(vec, mat);
	vec = mul_vm(vec, mat_scale(vec_new(320, 240, 0, 1)));
	return (vec);
}

int
	loop_hook(t_fdf *fdf)
{
	int		x;
	int		y;
	t_vec	from;
	t_vec	to;

	img_clear(fdf->img_ptr, 0x000000);
	x = 0;
	while (x < fdf->width)
	{
		y = 0;
		while (y < fdf->height)
		{
			from = vec_new(x - (float) fdf->width / 2 + 0.5, y - (float) fdf->height / 2 + 0.5, fdf->points[x + y * fdf->width], 1.0f);
			if (x != 0)
			{
				to = vec_new(x - 1 - (float) fdf->width / 2 + 0.5, y - (float) fdf->height / 2 + 0.5, fdf->points[x - 1 + y * fdf->width], 1.0f);
				img_line(fdf->img_ptr, trans(from, fdf->time), trans(to, fdf->time), 0xFF0000);
			}
			if (y != 0)
			{
				to = vec_new(x - (float) fdf->width / 2 + 0.5, y - 1 - (float) fdf->height / 2 + 0.5, fdf->points[x + (y - 1) * fdf->width], 1.0f);
				img_line(fdf->img_ptr, trans(from, fdf->time), trans(to, fdf->time), 0xFF0000);
			}
			y += 1;
		}
		x += 1;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	fdf->time += 0.025;
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
	main(void)
{
	t_fdf	fdf;
	int		points[9];

	points[0] = 0;
	points[1] = 0;
	points[2] = 0;
	points[3] = 0;
	points[4] = 1;
	points[5] = 0;
	points[6] = 0;
	points[7] = 0;
	points[8] = 0;
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 640, 480, "FdF");
	fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, 640, 480);
	fdf.points = points;
	fdf.width = 3;
	fdf.height = 3;
	fdf.time = 0;
	mlx_loop_hook(fdf.mlx_ptr, loop_hook, &fdf);
	mlx_key_hook(fdf.win_ptr, key_hook, &fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
