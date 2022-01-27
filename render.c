/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 15:46:46 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/27 16:27:37 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"

static t_mat
	compute_matrix(t_fdf *fdf)
{
	t_mat	mat;
	t_vec	min;
	t_vec	max;

	min = vec_new(-1, -(float) fdf->win_height / fdf->win_width, 1, 0);
	max = vec_new(+1, +(float) fdf->win_height / fdf->win_width, 1000, 0);
	mat = mat_identity();
	mat = mul_mm(mat_scale(vec_scale(fdf->scale, 2.0 / fdf->map_scale)), mat);
	mat = mul_mm(mat_rotate_z(fdf->rotate.el[0]), mat);
	mat = mul_mm(mat_rotate_x(fdf->rotate.el[1]), mat);
	mat = mul_mm(mat_translate(vec_new(0, 0, -2, 0)), mat);
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

	if (fdf->color_mode == 0)
	{
		return (vert.map_col);
	}
	else if (fdf->color_mode == 1)
	{
		tmp = 1 - (float)(vert.height + fdf->min) / (fdf->max - fdf->min);
		return (vec_new(0.8, tmp * 0.4 + 0.4, 0.8, 0));
	}
	else
	{
		tmp = (vert.pos.el[2] + 1);
		if (fdf->use_persp)
			tmp = tmp * 1.5 - 1;
		else
			tmp = tmp * 250;
		if (tmp < 0)
			tmp = 0;
		if (tmp > 1)
			tmp = 1;
		tmp = 1 - tmp;
		return (vec_new(tmp, tmp, tmp, 0));
	}
}

static int
	compute_clip(t_vec vec)
{
	if (vec.el[0] > vec.el[3] || vec.el[0] < -vec.el[3])
		return (1);
	if (vec.el[1] > vec.el[3] || vec.el[1] < -vec.el[3])
		return (1);
	if (vec.el[2] > vec.el[3] || vec.el[2] < -vec.el[3])
		return (1);
	return (0);
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
		vec.el[0] = (int)(i % fdf->map_width) - (fdf->map_width - 1) / 2.0;
		vec.el[1] = (int)(i / fdf->map_width) - (fdf->map_height - 1) / 2.0;
		vec.el[2] = fdf->map[i].height - (fdf->max + fdf->min) / 2.0;
		vec.el[3] = 1;
		vec = mul_vm(vec, mat);
		fdf->map[i].clip = compute_clip(vec);
		vec = vec_scale(vec, 1 / vec.el[3]);
		vec.el[0] = (vec.el[0] + 1) * fdf->win_width / 2;
		vec.el[1] = (vec.el[1] + 1) * fdf->win_height / 2;
		fdf->map[i].pos = vec;
		fdf->map[i].col = compute_color(fdf, fdf->map[i]);
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
		if (!fdf->map[i].clip)
		{
			if (i % fdf->map_width != 0 && !fdf->map[i - 1].clip)
				img_line(fdf, fdf->map[i], fdf->map[i - 1]);
			if (i / fdf->map_width != 0 && !fdf->map[i - fdf->map_width].clip)
				img_line(fdf, fdf->map[i], fdf->map[i - fdf->map_width]);
		}
		i += 1;
	}
}
