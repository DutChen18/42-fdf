/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 10:15:10 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/25 10:13:35 by csteenvo      ########   odam.nl         */
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
	**split_next_line(int fd, size_t *size)
{
	char	*line;
	char	**fields;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	fields = ft_split(line, ' ');
	free(line);
	fdf_assert(fields != NULL, "ft_split");
	*size = 0;
	while (fields[*size] != NULL)
		*size += 1;
	return (fields);
}

static t_vert
	*fdf_expand(t_vert *verts, size_t width, size_t height, char **fields)
{
	t_vert	*new_verts;
	size_t	i;

	new_verts = malloc(width * (height + 1) * sizeof(*new_verts));
	fdf_assert(new_verts != NULL, "malloc");
	i = 0;
	while (i < width * height)
	{
		new_verts[i] = verts[i];
		i += 1;
	}
	free(verts);
	i = 0;
	while (i < width)
	{
		new_verts[width * height + i].height = ft_atoi(fields[i]);
		new_verts[width * height + i].color = 0xff0000;
		i += 1;
	}
	return (new_verts);
}

void
	fdf_assert(int condition, const char *message)
{
	if (!condition)
	{
		ft_putendl_fd((char *) message, STDERR_FILENO);
		(void) message;
		exit(EXIT_FAILURE);
	}
}

t_vert
	*fdf_read(size_t *width, size_t *height, const char *filename)
{
	char	**fields;
	int		fd;
	t_vert	*verts;
	size_t	size;

	fd = open(filename, O_RDONLY);
	fdf_assert(fd >= 0, strerror(errno));
	fields = split_next_line(fd, &size);
	fdf_assert(fields != NULL, "zero height");
	fdf_assert(size != 0, "zero width");
	verts = NULL;
	*width = size;
	*height = 0;
	while (fields != NULL)
	{
		fdf_assert(size == *width, "width not equal");
		verts = fdf_expand(verts, *width, *height, fields);
		free(fields);
		*height += 1;
		fields = split_next_line(fd, &size);
	}
	close(fd);
	return (verts);
}
