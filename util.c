/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 10:15:10 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/02/01 08:50:20 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static char
	**split_next_line(t_fdf *fdf, size_t *size)
{
	char	*line;
	char	**fields;

	line = get_next_line(fdf->fd);
	if (line == NULL)
		return (NULL);
	fields = ft_split(line, ' ');
	free(line);
	fdf_assert(fdf, fields != NULL, "ft_split", NULL);
	fdf_assert(fdf, *fields != NULL, "empty line", fields);
	*size = 0;
	while (fields[*size] != NULL && *fields[*size] != '\n')
		*size += 1;
	return (fields);
}

static void
	fdf_parse(t_vert *vert, const char *field)
{
	int	color;

	vert->height = ft_atoi(field);
	vert->map_col = vec_new(0.5, 0.5, 0.5, 0);
	while (*field != '\0' && *field != 'x')
		field += 1;
	if (*field == '\0')
		return ;
	color = 0;
	while (ft_isalnum(*field))
	{
		color *= 16;
		if (ft_isdigit(*field))
			color += *field - '0';
		else if (*field <= 'Z')
			color += *field - 'A' + 10;
		else
			color += *field - 'a' + 10;
		field += 1;
	}
	vert->map_col.el[0] = (float)((color >> 0) & 0xFF) / 0xFF;
	vert->map_col.el[1] = (float)((color >> 8) & 0xFF) / 0xFF;
	vert->map_col.el[2] = (float)((color >> 16) & 0xFF) / 0xFF;
}

static void
	fdf_expand(t_fdf *fdf, char **fields)
{
	t_vert	*new_verts;
	size_t	i;

	if ((fdf->map_height & (fdf->map_height - 1)) == 0)
	{
		i = fdf->map_width * fdf->map_height;
		if (fdf->map_height == 0)
			new_verts = malloc(fdf->map_width * sizeof(*new_verts));
		else
			new_verts = malloc(i * 2 * sizeof(*new_verts));
		fdf_assert(fdf, new_verts != NULL, "malloc", NULL);
		ft_memcpy(new_verts, fdf->map, i * sizeof(*fdf->map));
		free(fdf->map);
		fdf->map = new_verts;
	}
	i = 0;
	while (i < fdf->map_width)
	{
		fdf_parse(&fdf->map[fdf->map_width * fdf->map_height + i], fields[i]);
		i += 1;
	}
}

void
	fdf_assert(t_fdf *fdf, int condition, const char *message, void *ptr)
{
	if (!condition)
	{
		free(ptr);
		if (fdf->fd != -1)
			close(fdf->fd);
		ft_putendl_fd((char *) message, STDERR_FILENO);
		fdf_exit(fdf, EXIT_FAILURE);
	}
}

void
	fdf_read(t_fdf *fdf, const char *filename)
{
	char	**fields;
	size_t	size;

	fdf->fd = open(filename, O_RDONLY);
	fdf_assert(fdf, fdf->fd >= 0, strerror(errno), NULL);
	fields = split_next_line(fdf, &size);
	fdf_assert(fdf, fields != NULL, "empty file", NULL);
	fdf->map_width = size;
	fdf->map_height = 0;
	while (fields != NULL)
	{
		fdf_assert(fdf, size >= fdf->map_width, "line too short", fields);
		fdf_expand(fdf, fields);
		free(fields);
		fdf->map_height += 1;
		fields = split_next_line(fdf, &size);
	}
	close(fdf->fd);
	fdf->fd = -1;
}
