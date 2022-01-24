/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 13:39:56 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/24 13:40:01 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# error BUFFER_SIZE not defined
#elif !(BUFFER_SIZE > 0)
# error BUFFER_SIZE not greater than 0
#endif

char
	*ft_realloc(char *oldptr, size_t newsize, size_t oldsize)
{
	char	*newptr;

	newptr = malloc(newsize);
	if (newptr == NULL)
	{
		free(oldptr);
		return (NULL);
	}
	while (0 < oldsize)
	{
		oldsize -= 1;
		newptr[oldsize] = oldptr[oldsize];
	}
	free(oldptr);
	return (newptr);
}

int
	push_char(char ch, t_line *line)
{
	if (line->size == line->maxsize)
	{
		line->data = ft_realloc(line->data, line->maxsize * 2, line->maxsize);
		line->maxsize *= 2;
		if (line->data == NULL)
			return (-1);
	}
	line->data[line->size] = ch;
	line->size += 1;
	return (0);
}

int
	read_line(int fd, t_line *line, t_file *file)
{
	ssize_t	size;

	while (1)
	{
		if (file->offset >= file->size)
		{
			size = read(fd, file->buffer, BUFFER_SIZE);
			if (size <= 0)
				return (-(!line->size || size < 0));
			file->size = size;
			file->offset = 0;
		}
		if (push_char(file->buffer[file->offset], line) < 0)
			return (-1);
		file->offset += 1;
		if (line->data[line->size - 1] == '\n')
			return (0);
	}
}
