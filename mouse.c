/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 11:29:12 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/25 15:03:54 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int
	mouse_down_hook(int button, int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;
	if (button == 1)
		fdf->mouse_1_down = 1;
	if (button == 2)
		fdf->mouse_2_down = 1;
	if (button == 4)
		fdf->scale = vec_scale(fdf->scale, pow(2, 1.0 / 4));
	if (button == 5)
		fdf->scale = vec_scale(fdf->scale, 1 / pow(2, 1.0 / 4));
	return (0);
}

int
	mouse_up_hook(int button, int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;
	if (button == 1)
		fdf->mouse_1_down = 0;
	if (button == 2)
		fdf->mouse_2_down = 0;
	return (0);
}

int
	mouse_moved_hook(int x, int y, t_fdf *fdf)
{
	if (fdf->mouse_1_down)
	{
		fdf->rotate.el[0] -= (float)(x - fdf->mouse_x) / fdf->win_height * 4;
		fdf->rotate.el[1] -= (float)(y - fdf->mouse_y) / fdf->win_height * 4;
		if (fdf->rotate.el[1] > M_PI / 2 - M_PI / 16)
			fdf->rotate.el[1] = M_PI / 2 - M_PI / 16;
		if (fdf->rotate.el[1] < M_PI / 16)
			fdf->rotate.el[1] = M_PI / 16;
	}
	if (fdf->mouse_2_down)
	{
		fdf->translate.el[0] += (float)(x - fdf->mouse_x) / fdf->win_height * 3;
		fdf->translate.el[1] += (float)(y - fdf->mouse_y) / fdf->win_height * 3;
	}
	fdf->mouse_x = x;
	fdf->mouse_y = y;
	return (0);
}
