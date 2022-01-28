/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 10:00:25 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/28 13:50:12 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec
	vec_new(float x, float y, float z, float w)
{
	t_vec	vec;

	vec.el[0] = x;
	vec.el[1] = y;
	vec.el[2] = z;
	vec.el[3] = w;
	return (vec);
}

t_mat
	mat_new(t_vec x, t_vec y, t_vec z, t_vec w)
{
	t_mat	mat;

	mat.el[0] = x;
	mat.el[1] = y;
	mat.el[2] = z;
	mat.el[3] = w;
	return (mat);
}

t_mat
	mat_identity(void)
{
	return (mat_new(
			vec_new(1, 0, 0, 0),
			vec_new(0, 1, 0, 0),
			vec_new(0, 0, 1, 0),
			vec_new(0, 0, 0, 1)));
}

t_mat
	mat_ortho(t_vec min, t_vec max)
{
	t_vec	v1;
	t_vec	v2;

	v1 = vec_new(
			2 / (max.el[0] - min.el[0]),
			2 / (max.el[1] - min.el[1]),
			2 / (min.el[2] - max.el[2]), 0);
	v2 = vec_new(
			(max.el[0] + min.el[0]) / (min.el[0] - max.el[0]),
			(max.el[1] + min.el[1]) / (min.el[1] - max.el[1]),
			(max.el[2] + min.el[2]) / (min.el[2] - max.el[2]), 0);
	return (mat_new(
			vec_new(v1.el[0], 0, 0, v2.el[0]),
			vec_new(0, v1.el[1], 0, v2.el[1]),
			vec_new(0, 0, v1.el[2], v2.el[2]),
			vec_new(0, 0, 0, 1)));
}

t_mat
	mat_persp(t_vec min, t_vec max)
{
	t_vec	v1;
	t_vec	v2;

	v1 = vec_new(
			2 * min.el[2] / (max.el[0] - min.el[0]),
			2 * min.el[2] / (max.el[1] - min.el[1]),
			2 * min.el[2] / (min.el[2] - max.el[2]) * max.el[2], 0);
	v2 = vec_new(
			(max.el[0] + min.el[0]) / (max.el[0] - min.el[0]),
			(max.el[1] + min.el[1]) / (max.el[1] - min.el[1]),
			(max.el[2] + min.el[2]) / (min.el[2] - max.el[2]), 0);
	return (mat_new(
			vec_new(v1.el[0], 0, v2.el[0], 0),
			vec_new(0, v1.el[1], v2.el[1], 0),
			vec_new(0, 0, v2.el[2], v1.el[2]),
			vec_new(0, 0, -1, 0)));
}
