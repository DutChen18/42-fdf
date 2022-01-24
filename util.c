/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 10:15:10 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/24 10:17:08 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void
	fdf_assert(int condition, const char *message)
{
	if (!condition)
	{
		(void) message;
		exit(EXIT_FAILURE);
	}
}
