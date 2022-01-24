/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 15:46:46 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/24 16:16:16 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <math.h>

static t_vec
	trans(t_fdf *fdf, t_vec vec, float time)
{
	t_mat	mat;

	mat = mat_ortho(
			vec_new(-4.0f, -3.0f, -1.0f, 0.0f),
			vec_new(0.0f, 0.0f, 1.0f, 0.0f));
	vec = mul_vm(vec, mat_rotate_z(time));
	vec = mul_vm(vec, mat_rotate_z(M_PI / 4));
	vec = mul_vm(vec, mat_rotate_x(M_PI / 4));
	vec = mul_vm(vec, mat);
	vec = mul_vm(vec, mat_scale(vec_new(
					fdf->win_width / 2.0, fdf->win_height / 2.0, 0, 1)));
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
		fdf->map[i].pos = trans(fdf, fdf->map[i].pos, 0);
		i += 1;
	}
}

void
	fdf_render(t_fdf *fdf)
{
	size_t	i;
	int		tmp;

	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		if (i % fdf->map_width != 0)
			img_line(fdf, fdf->map[i], fdf->map[i - 1]);
		if (i / fdf->map_width != 0)
			img_line(fdf, fdf->map[i], fdf->map[i - fdf->map_width]);
		i += 1;
	}
	tmp = mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	fdf_assert(tmp, "mlx_put_image_to_window");
}
