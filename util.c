/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 10:00:25 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/20 16:17:38 by csteenvo      ########   odam.nl         */
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
			vec_new(1.0f, 0.0f, 0.0f, 0.0f),
			vec_new(0.0f, 1.0f, 0.0f, 0.0f),
			vec_new(0.0f, 0.0f, 1.0f, 0.0f),
			vec_new(0.0f, 0.0f, 0.0f, 1.0f)));
}

t_mat
	mat_ortho(t_vec min, t_vec max)
{
	t_mat	scale;
	t_mat	translate;

	scale = mat_scale(vec_new(
				2.0f / (max.el[0] - min.el[0]),
				2.0f / (max.el[1] - min.el[1]),
				2.0f / (min.el[2] - max.el[2]), 0.0f));
	translate = mat_translate(vec_new(
				-(max.el[0] + min.el[0]) / (max.el[0] - min.el[0]),
				-(max.el[1] + min.el[1]) / (max.el[1] - min.el[1]),
				-(max.el[2] + min.el[2]) / (max.el[2] - min.el[2]), 0.0f));
	return (mul_mm(translate, scale));
}
