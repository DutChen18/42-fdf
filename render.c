/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 15:46:46 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/27 12:20:12 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"

static t_mat
	compute_matrix(t_fdf *fdf)
{
	t_mat	proj;
	t_mat	mat;
	float	scale;

	if (fdf->map_width > fdf->map_height)
		scale = 2.0 / (fdf->map_width + (fdf->max - fdf->min) / 2.0);
	else
		scale = 2.0 / (fdf->map_height + (fdf->max - fdf->min) / 2.0);
	if (fdf->use_persp)
		proj = mat_persp(
				vec_new(-4, -3, 1, 0),
				vec_new(4, 3, 100, 0));
	else
		proj = mat_ortho(
				vec_new(-4, -3, -100, 0),
				vec_new(4, 3, 100, 0));
	mat = mat_scale(vec_new(scale, scale, scale, 1));
	mat = mul_mm(mat_scale(fdf->scale), mat);
	mat = mul_mm(mat_rotate_z(fdf->rotate.el[0]), mat);
	mat = mul_mm(mat_rotate_x(fdf->rotate.el[1]), mat);
	mat = mul_mm(mat_translate(fdf->translate), mat);
	mat = mul_mm(proj, mat);
	return (mat);
}

void
	fdf_update(t_fdf *fdf)
{
	size_t	i;
	t_vec	vec;
	t_mat	mat;
	float	tmp;

	i = 0;
	mat = compute_matrix(fdf);
	while (i < fdf->map_width * fdf->map_height)
	{
		vec.el[0] = (int)(i % fdf->map_width) - fdf->map_width / 2.0 + 0.5;
		vec.el[1] = (int)(i / fdf->map_width) - fdf->map_height / 2.0 + 0.5;
		vec.el[2] = fdf->map[i].height - (fdf->max + fdf->min) / 2.0;
		vec.el[3] = 1;
		vec = mul_vm(vec, mat);
		vec = vec_scale(vec, 1 / vec.el[3]);
		vec.el[0] = (vec.el[0] + 0.5) * fdf->win_width;
		vec.el[1] = (vec.el[1] + 0.5) * fdf->win_height;
		fdf->map[i].pos = vec;
		tmp = 1.0 - (float) fdf->map[i].height / (fdf->max - fdf->min) * 0.99;
		if (fdf->color_mode == 0)
			fdf->map[i].col = fdf->map[i].map_col;
		else
			fdf->map[i].col = vec_new(0.8, tmp * 0.4 + 0.4, 0.8, 0);
		i += 1;
	}
}

void
	fdf_render(t_fdf *fdf)
{
	size_t	i;

	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		if (fdf->map[i].pos.el[2] < 1)
		{
			if (i % fdf->map_width != 0)
				if (fdf->map[i - 1].pos.el[2] < 1)
					img_line(fdf, fdf->map[i], fdf->map[i - 1]);
			if (i / fdf->map_width != 0)
				if (fdf->map[i - fdf->map_width].pos.el[2] < 1)
					img_line(fdf, fdf->map[i], fdf->map[i - fdf->map_width]);
		}
		i += 1;
	}
}
