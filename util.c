/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 10:15:10 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/28 14:22:36 by csteenvo      ########   odam.nl         */
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
	fdf_assert(*fields != NULL, "empty line");
	*size = 0;
	while (fields[*size] != NULL)
		*size += 1;
	return (fields);
}

static void
	fdf_parse(t_vert *vert, const char *field)
{
	int	color;

	vert->height = ft_atoi(field);
	vert->map_col = vec_new(0.8f, 0.8f, 0.8f, 0);
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

static t_vert
	*fdf_expand(t_vert *verts, size_t width, size_t height, char **fields)
{
	t_vert	*new_verts;
	size_t	i;

	if ((height & (height - 1)) == 0)
	{
		if (height == 0)
			new_verts = malloc(width * sizeof(*new_verts));
		else
			new_verts = malloc(width * height * 2 * sizeof(*new_verts));
		fdf_assert(new_verts != NULL, "malloc");
		ft_memcpy(new_verts, verts, width * height * sizeof(*verts));
		free(verts);
		verts = new_verts;
	}
	i = 0;
	while (i < width)
	{
		fdf_parse(&verts[width * height + i], fields[i]);
		i += 1;
	}
	return (verts);
}

void
	fdf_assert(int condition, const char *message)
{
	if (!condition)
	{
		ft_putendl_fd((char *) message, STDERR_FILENO);
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
	fdf_assert(fields != NULL, "empty file");
	verts = NULL;
	*width = size;
	*height = 0;
	while (fields != NULL)
	{
		fdf_assert(size >= *width, "line too short");
		verts = fdf_expand(verts, *width, *height, fields);
		free(fields);
		*height += 1;
		fields = split_next_line(fd, &size);
	}
	close(fd);
	return (verts);
}
