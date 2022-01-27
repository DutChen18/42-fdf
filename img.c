/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 11:51:39 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/27 12:00:08 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <math.h>

void
	img_put(t_fdf *fdf, t_vec pos, t_vec col)
{
	int	x;
	int	y;

	x = pos.el[0];
	y = pos.el[1];
	if (x < 0 || x >= fdf->win_width)
		return ;
	if (y < 0 || y >= fdf->win_height)
		return ;
	if (pos.el[2] > fdf->depth[x + y * fdf->win_width])
		return ;
	fdf->color[x * 4 + y * fdf->img_size + 0] = col.el[0] * 0xFF;
	fdf->color[x * 4 + y * fdf->img_size + 1] = col.el[1] * 0xFF;
	fdf->color[x * 4 + y * fdf->img_size + 2] = col.el[2] * 0xFF;
	fdf->color[x * 4 + y * fdf->img_size + 3] = col.el[3] * 0xFF;
	fdf->depth[x + y * fdf->win_width] = pos.el[2];
}

void
	img_clear(t_fdf *fdf, t_vec col)
{
	int	i;

	i = 0;
	while (i < fdf->win_width * fdf->win_height)
	{
		fdf->color[i * 4 + 0] = col.el[0] * 0xFF;
		fdf->color[i * 4 + 1] = col.el[1] * 0xFF;
		fdf->color[i * 4 + 2] = col.el[2] * 0xFF;
		fdf->depth[i] = INFINITY;
		i += 1;
	}
}

void
	img_line(t_fdf *fdf, t_vert from, t_vert to)
{
	t_vec	pos_delta;
	t_vec	col_delta;
	float	step;
	int		i;

	pos_delta = vec_sub(to.pos, from.pos);
	col_delta = vec_sub(to.col, from.col);
	if (fabs(pos_delta.el[0]) > fabs(pos_delta.el[1]))
		step = fabs(pos_delta.el[0]);
	else
		step = fabs(pos_delta.el[1]);
	pos_delta = vec_scale(pos_delta, 1 / step);
	col_delta = vec_scale(col_delta, 1 / step);
	i = 0;
	while (i <= step)
	{
		img_put(fdf, from.pos, from.col);
		from.pos = vec_add(from.pos, pos_delta);
		from.col = vec_add(from.col, col_delta);
		i += 1;
	}
}
