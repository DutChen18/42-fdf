/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 12:34:41 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/02/01 08:18:56 by csteenvo      ########   odam.nl         */
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

t_vec
	vec_add(t_vec lhs, t_vec rhs)
{
	return (vec_new(
			lhs.el[0] + rhs.el[0],
			lhs.el[1] + rhs.el[1],
			lhs.el[2] + rhs.el[2],
			lhs.el[3] + rhs.el[3]));
}

t_vec
	vec_sub(t_vec lhs, t_vec rhs)
{
	return (vec_new(
			lhs.el[0] - rhs.el[0],
			lhs.el[1] - rhs.el[1],
			lhs.el[2] - rhs.el[2],
			lhs.el[3] - rhs.el[3]));
}

t_vec
	vec_scale(t_vec lhs, float rhs)
{
	return (vec_new(
			lhs.el[0] * rhs,
			lhs.el[1] * rhs,
			lhs.el[2] * rhs,
			lhs.el[3] * rhs));
}
