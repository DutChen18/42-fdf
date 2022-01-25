/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 15:46:46 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/25 16:24:57 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <math.h>

static t_mat
	compute_matrix(t_fdf *fdf)
{
	t_mat	proj;
	t_mat	mat;
	float	scale;

	if (fdf->map_width > fdf->map_height)
		scale = 2.0 / fdf->map_width;
	else
		scale = 2.0 / fdf->map_height;
	if (fdf->use_persp)
		proj = mat_persp(
				vec_new(-4, -3, 1, 0),
				vec_new(4, 3, 100, 0));
	else
		proj = mat_ortho(
				vec_new(-4, -3, 1, 0),
				vec_new(4, 3, 100, 0));
	mat = mat_scale(vec_new(scale, scale, scale, 1));
	mat = mul_mm(mat_rotate_z(fdf->rotate.el[0]), mat);
	mat = mul_mm(mat_rotate_x(fdf->rotate.el[1]), mat);
	mat = mul_mm(mat_scale(fdf->scale), mat);
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

	i = 0;
	mat = compute_matrix(fdf);
	while (i < fdf->map_width * fdf->map_height)
	{
		vec.el[0] = (int)(i % fdf->map_width) - fdf->map_width / 2.0 + 0.5;
		vec.el[1] = (int)(i / fdf->map_width) - fdf->map_height / 2.0 + 0.5;
		vec.el[2] = fdf->map[i].height;
		vec.el[3] = 1;
		vec = mul_vm(vec, mat);
		vec = vec_scale(vec, 1 / vec.el[3]);
		vec.el[0] = (vec.el[0] + 0.5) * fdf->win_width;
		vec.el[1] = (vec.el[1] + 0.5) * fdf->win_height;
		fdf->map[i].pos = vec;
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
		if (i % fdf->map_width != 0)
			img_line(fdf, fdf->map[i], fdf->map[i - 1]);
		if (i / fdf->map_width != 0)
			img_line(fdf, fdf->map[i], fdf->map[i - fdf->map_width]);
		i += 1;
	}
}
