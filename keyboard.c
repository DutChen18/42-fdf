/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 11:18:44 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/02/01 08:48:11 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>

void
	fdf_exit(t_fdf *fdf, int status)
{
	if (fdf->img != NULL)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win != NULL)
		mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf->map);
	free(fdf->depth);
	exit(status);
}

int
	close_hook(t_fdf *fdf)
{
	fdf_exit(fdf, EXIT_SUCCESS);
	return (0);
}

int
	key_down_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53 || keycode == 12)
		fdf_exit(fdf, EXIT_SUCCESS);
	if (keycode == 35)
		fdf->use_persp = !fdf->use_persp;
	if (keycode == 3)
		fdf->use_fog = !fdf->use_fog;
	if (keycode == 126)
		fdf->scale.el[2] *= 2;
	if (keycode == 125)
		fdf->scale.el[2] /= 2;
	if (keycode == 8)
		fdf->color_mode = (fdf->color_mode + 1) % 3;
	if (keycode == 18)
		fdf->draw_mode = 0;
	if (keycode == 19)
		fdf->draw_mode = 1;
	return (0);
}

int
	key_up_hook(int keycode, t_fdf *fdf)
{
	(void) keycode;
	(void) fdf;
	return (0);
}
