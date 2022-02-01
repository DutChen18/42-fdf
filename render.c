/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 15:46:46 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/02/01 08:10:54 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <math.h>

static t_mat
	compute_matrix(t_fdf *fdf)
{
	t_mat	mat;
	t_vec	min;
	t_vec	max;

	min = vec_new(-1, -(float) fdf->win_height / fdf->win_width, 1, 0);
	max = vec_new(+1, +(float) fdf->win_height / fdf->win_width, 2, 0);
	mat = mat_identity();
	mat = mul_mm(mat_scale(fdf->scale), mat);
	mat = mul_mm(mat_rotate_z(fdf->rotate.el[0]), mat);
	mat = mul_mm(mat_rotate_x(fdf->rotate.el[1]), mat);
	mat = mul_mm(mat_translate(vec_new(0, 0, -1, 0)), mat);
	mat = mul_mm(mat_translate(fdf->translate), mat);
	if (fdf->use_persp)
		mat = mul_mm(mat_persp(min, max), mat);
	else
		mat = mul_mm(mat_ortho(min, max), mat);
	return (mat);
}

static t_vec
	compute_color(t_fdf *fdf, t_vert vert)
{
	float	tmp;
	t_vec	vec;

	tmp = 1 - (float)(vert.height - fdf->min) / (fdf->max - fdf->min);
	if (fdf->color_mode == 0)
		vec = vert.map_col;
	else if (fdf->color_mode == 1)
		vec = vec_new(0.8, tmp * 0.4 + 0.4, 0.8, 0);
	else
		vec = vec_new(1, 1, 1, 0);
	if (fdf->use_fog)
	{
		tmp = 1 - (vert.pos.el[2] / vert.pos.el[3] + 2) / 2;
		if (tmp > 1)
			tmp = 1;
		if (tmp < 0)
			tmp = 0;
		vec = vec_scale(vec, tmp);
	}
	return (vec);
}

static void
	draw(t_fdf *fdf)
{
	size_t	i;
	t_vert	vert;

	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		vert = fdf->map[i];
		if (fdf->draw_mode == 0)
		{
			if (i % fdf->map_width != 0)
				clip_line(fdf, vert, fdf->map[i - 1]);
			if (i / fdf->map_width != 0)
				clip_line(fdf, vert, fdf->map[i - fdf->map_width]);
		}
		else
		{
			if (clip(vert.pos))
				img_put(fdf, clip_convert(fdf, vert.pos), vert.col);
		}
		i += 1;
	}
}

void
	fdf_render(t_fdf *fdf)
{
	size_t	i;
	t_vec	vec;
	t_mat	mat;

	i = 0;
	mat = compute_matrix(fdf);
	while (i < fdf->map_width * fdf->map_height)
	{
		vec.el[0] = (int)(i % fdf->map_width) - (fdf->map_width - 1) / 2.0;
		vec.el[1] = (int)(i / fdf->map_width) - (fdf->map_height - 1) / 2.0;
		vec.el[2] = fdf->map[i].height - (fdf->max + fdf->min) / 2.0;
		vec.el[3] = 1;
		fdf->map[i].pos = mul_vm(vec, mat);
		fdf->map[i].col = compute_color(fdf, fdf->map[i]);
		i += 1;
	}
	draw(fdf);
}
