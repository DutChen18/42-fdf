/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 13:39:22 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/24 13:39:27 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifdef BUFFER_SIZE
#  include <stddef.h>

typedef struct s_file	t_file;
typedef struct s_line	t_line;

struct s_file
{
	size_t	offset;
	size_t	size;
	char	buffer[BUFFER_SIZE];
};

struct s_line
{
	size_t	size;
	size_t	maxsize;
	char	*data;
};

char	*ft_realloc(char *oldptr, size_t newsize, size_t oldsize);
int		push_char(char ch, t_line *line);
int		read_line(int fd, t_line *line, t_file *file);
# endif

char	*get_next_line(int fd);

#endif
