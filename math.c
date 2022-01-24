/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:44:31 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/24 16:06:29 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec
	mat_column(t_mat lhs, int rhs)
{
	return (vec_new(
			lhs.el[0].el[rhs],
			lhs.el[1].el[rhs],
			lhs.el[2].el[rhs],
			lhs.el[3].el[rhs]));
}

t_mat
	mat_transpose(t_mat lhs)
{
	return (mat_new(
			mat_column(lhs, 0),
			mat_column(lhs, 1),
			mat_column(lhs, 2),
			mat_column(lhs, 3)));
}

float
	mul_vv(t_vec lhs, t_vec rhs)
{
	return (0.0f
		+ lhs.el[0] * rhs.el[0]
		+ lhs.el[1] * rhs.el[1]
		+ lhs.el[2] * rhs.el[2]
		+ lhs.el[3] * rhs.el[3]);
}

t_vec
	mul_vm(t_vec lhs, t_mat rhs)
{
	return (vec_new(
			mul_vv(lhs, rhs.el[0]),
			mul_vv(lhs, rhs.el[1]),
			mul_vv(lhs, rhs.el[2]),
			mul_vv(lhs, rhs.el[3])));
}

t_mat
	mul_mm(t_mat lhs, t_mat rhs)
{
	rhs = mat_transpose(rhs);
	return (mat_new(
			mul_vm(lhs.el[0], rhs),
			mul_vm(lhs.el[1], rhs),
			mul_vm(lhs.el[2], rhs),
			mul_vm(lhs.el[3], rhs)));
}
