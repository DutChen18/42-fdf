/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 11:18:44 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/27 12:22:44 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>

int
	close_hook(t_fdf *fdf)
{
	(void) fdf;
	exit(EXIT_SUCCESS);
	return (0);
}

int
	key_down_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53 || keycode == 12)
		exit(EXIT_SUCCESS);
	if (keycode == 35)
		fdf->use_persp = !fdf->use_persp;
	if (keycode == 126)
		fdf->scale.el[2] *= 2;
	if (keycode == 125)
		fdf->scale.el[2] /= 2;
	if (keycode == 8)
		fdf->color_mode = (fdf->color_mode + 1) % 3;
	return (0);
}

int
	key_up_hook(int keycode, t_fdf *fdf)
{
	(void) keycode;
	(void) fdf;
	return (0);
}