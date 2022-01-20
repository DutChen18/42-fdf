/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 11:51:39 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/20 14:44:53 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"
#include <math.h>

void
	img_put(void *img, int x, int y, int color)
{
	char	*data;
	int		bpp;
	int		size;
	int		endian;

	if (x < 0 || x >= FDF_WIDTH)
		return ;
	if (y < 0 || y >= FDF_HEIGHT)
		return ;
	data = mlx_get_data_addr(img, &bpp, &size, &endian);
	data[x * 4 + y * size + 0] = color >> 0 & 0xFF;
	data[x * 4 + y * size + 1] = color >> 8 & 0xFF;
	data[x * 4 + y * size + 2] = color >> 16 & 0xFF;
	data[x * 4 + y * size + 3] = color >> 24 & 0xFF;
}

void
	img_clear(void *img, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < FDF_WIDTH)
	{
		y = 0;
		while (y < FDF_HEIGHT)
		{
			img_put(img, x, y, color);
			y += 1;
		}
		x += 1;
	}
}

void
	img_line(void *img, t_vec from, t_vec to, int color)
{
	float	dx;
	float	dy;
	float	step;
	int		i;

	dx = (to.el[0] - from.el[0]);
	dy = (to.el[1] - from.el[1]);
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	i = 0;
	while (i <= step)
	{
		img_put(img, from.el[0], from.el[1], color);
		from.el[0] += dx;
		from.el[1] += dy;
		i += 1;
	}
}
