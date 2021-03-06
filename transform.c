/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 10:00:25 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/25 15:07:28 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_mat
	mat_translate(t_vec	v)
{
	return (mat_new(
			vec_new(1, 0, 0, v.el[0]),
			vec_new(0, 1, 0, v.el[1]),
			vec_new(0, 0, 1, v.el[2]),
			vec_new(0, 0, 0, 1)));
}

t_mat
	mat_scale(t_vec v)
{
	return (mat_new(
			vec_new(v.el[0], 0, 0, 0),
			vec_new(0, v.el[1], 0, 0),
			vec_new(0, 0, v.el[2], 0),
			vec_new(0, 0, 0, 1)));
}

t_mat
	mat_rotate_x(float v)
{
	return (mat_new(
			vec_new(1, 0, 0, 0),
			vec_new(0, cos(v), -sin(v), 0),
			vec_new(0, sin(v), cos(v), 0),
			vec_new(0, 0, 0, 1)));
}

t_mat
	mat_rotate_y(float v)
{
	return (mat_new(
			vec_new(cos(v), 0, sin(v), 0),
			vec_new(0, 1, 0, 0),
			vec_new(-sin(v), 0, cos(v), 0),
			vec_new(0, 0, 0, 1)));
}

t_mat
	mat_rotate_z(float v)
{
	return (mat_new(
			vec_new(cos(v), -sin(v), 0, 0),
			vec_new(sin(v), cos(v), 0, 0),
			vec_new(0, 0, 1, 0),
			vec_new(0, 0, 0, 1)));
}
