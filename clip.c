/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clip.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/28 16:08:46 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/02/01 08:54:59 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int
	clip_axis(t_vert *from, t_vert to, int axis, float sign)
{
	float	scale;

	if (from->pos.el[axis] * sign < from->pos.el[3])
		return (0);
	if (to.pos.el[axis] * sign > to.pos.el[3])
		return (1);
	scale = to.pos.el[3] - to.pos.el[axis] * sign;
	scale = scale / (scale - (from->pos.el[3] - from->pos.el[axis] * sign));
	from->pos = vec_add(vec_scale(vec_sub(from->pos, to.pos), scale), to.pos);
	from->col = vec_add(vec_scale(vec_sub(from->col, to.col), scale), to.col);
	return (0);
}

static t_vec
	clip_convert(t_fdf *fdf, t_vec vec)
{
	vec = vec_scale(vec, 1 / vec.el[3]);
	vec.el[0] = (vec.el[0] + 1) * fdf->win_width / 2;
	vec.el[1] = (vec.el[1] + 1) * fdf->win_height / 2;
	return (vec);
}

void
	clip_line(t_fdf *fdf, t_vert from, t_vert to)
{
	if (clip_axis(&from, to, 0, 1) || clip_axis(&from, to, 0, -1))
		return ;
	if (clip_axis(&from, to, 1, 1) || clip_axis(&from, to, 1, -1))
		return ;
	if (clip_axis(&to, from, 0, 1) || clip_axis(&to, from, 0, -1))
		return ;
	if (clip_axis(&to, from, 1, 1) || clip_axis(&to, from, 1, -1))
		return ;
	from.pos = clip_convert(fdf, from.pos);
	to.pos = clip_convert(fdf, to.pos);
	img_line(fdf, from, to);
}

void
	clip_point(t_fdf *fdf, t_vert vert)
{
	if (vert.pos.el[0] > vert.pos.el[3] || vert.pos.el[0] < -vert.pos.el[3])
		return ;
	if (vert.pos.el[1] > vert.pos.el[3] || vert.pos.el[1] < -vert.pos.el[3])
		return ;
	vert.pos = clip_convert(fdf, vert.pos);
	img_put(fdf, vert.pos, vert.col);
}
