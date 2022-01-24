/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 11:51:39 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/24 10:21:22 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <math.h>

void
	img_put(t_fdf *fdf, int x, int y, int color)
{
	char	*data;
	int		bpp;
	int		size;
	int		endian;

	if (x < 0 || x >= fdf->win_width)
		return ;
	if (y < 0 || y >= fdf->win_height)
		return ;
	data = mlx_get_data_addr(fdf->img_ptr, &bpp, &size, &endian);
	fdf_assert(data != NULL, "mlx_get_data_addr");
	data[x * 4 + y * size + 0] = color >> 0 & 0xFF;
	data[x * 4 + y * size + 1] = color >> 8 & 0xFF;
	data[x * 4 + y * size + 2] = color >> 16 & 0xFF;
	data[x * 4 + y * size + 3] = color >> 24 & 0xFF;
}

void
	img_clear(t_fdf *fdf, int color)
{
	int	i;

	i = 0;
	while (i < fdf->win_width * fdf->win_height)
	{
		img_put(fdf, i % fdf->win_width, i / fdf->win_height, color);
		i += 1;
	}
}

void
	img_line(t_fdf *fdf, t_vert from, t_vert to)
{
	t_vec	delta;
	float	step;
	int		i;

	delta.el[0] = (to.pos.el[0] - from.pos.el[0]);
	delta.el[1] = (to.pos.el[1] - from.pos.el[1]);
	if (fabs(delta.el[0]) > fabs(delta.el[1]))
		step = fabs(delta.el[0]);
	else
		step = fabs(delta.el[1]);
	delta.el[0] /= step;
	delta.el[1] /= step;
	i = 0;
	while (i <= step)
	{
		img_put(fdf, from.pos.el[0], from.pos.el[1], from.color);
		from.pos.el[0] += delta.el[0];
		from.pos.el[1] += delta.el[1];
		i += 1;
	}
}
