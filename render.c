/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 15:46:46 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/25 12:01:41 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>

static t_vec
	trans(t_fdf *fdf, t_vec vec)
{
	t_mat	mat;

	if (fdf->projection)
	{
		mat = mat_persp(
				vec_new(-4.0f, -3.0f, 1.0f, 0.0f),
				vec_new(4.0f, 3.0f, 100.0f, 0.0f));
	}
	else
	{
		mat = mat_ortho(
				vec_new(-4.0f, -3.0f, 1.0f, 0.0f),
				vec_new(4.0f, 3.0f, 100.0f, 0.0f));
	}
	vec = mul_vm(vec, mat_rotate_z(fdf->rot_x));
	vec = mul_vm(vec, mat_rotate_x(fdf->rot_y));
	vec = mul_vm(vec, mat_scale(vec_new(fdf->scale, fdf->scale, fdf->scale, 0)));
	vec = mul_vm(vec, mat_translate(vec_new(fdf->translate_x, fdf->translate_y, 0, 0)));
	vec.el[2] -= 1.0f;
	vec = mul_vm(vec, mat);
	vec.el[0] /= vec.el[3];
	vec.el[1] /= vec.el[3];
	vec.el[2] /= vec.el[3];
	vec.el[3] /= vec.el[3];
	vec.el[0] = (vec.el[0] + 0.5f) * fdf->win_width;
	vec.el[1] = (vec.el[1] + 0.5f) * fdf->win_height;
	return (vec);
}

void
	fdf_update(t_fdf *fdf)
{
	size_t	i;
	float	x;
	float	y;
	float	s;

	i = 0;
	if (fdf->map_width > fdf->map_height)
		s = fdf->map_width / 2.0;
	else
		s = fdf->map_height / 2.0;
	while (i < fdf->map_width * fdf->map_height)
	{
		x = (int)(i % fdf->map_width) - fdf->map_width / 2.0f + 0.5f;
		y = (int)(i / fdf->map_width) - fdf->map_height / 2.0f + 0.5f;
		fdf->map[i].pos = vec_new(x / s, y / s, fdf->map[i].height / s, 1);
		fdf->map[i].pos = trans(fdf, fdf->map[i].pos);
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
