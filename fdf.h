/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:20:27 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/20 16:27:49 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stddef.h>

# ifndef FDF_WIDTH
#  define FDF_WIDTH 640
# endif
# ifndef FDF_HEIGHT
#  define FDF_HEIGHT 480
# endif

typedef struct s_vec	t_vec;
typedef struct s_mat	t_mat;
typedef struct s_fdf	t_fdf;

struct s_vec {
	float	el[4];
};

struct s_mat {
	t_vec	el[4];
};

struct s_fdf {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*points;
	int		width;
	int		height;
	float	time;
};

float	mul_vv(t_vec lhs, t_vec rhs);
t_vec	mul_vm(t_vec lhs, t_mat rhs);
t_mat	mul_mm(t_mat lhs, t_mat rhs);

t_mat	mat_translate(t_vec	v);
t_mat	mat_scale(t_vec v);
t_mat	mat_rotate_x(float v);
t_mat	mat_rotate_y(float v);
t_mat	mat_rotate_z(float v);

t_vec	vec_new(float x, float y, float z, float w);
t_mat	mat_new(t_vec x, t_vec y, t_vec z, t_vec w);
t_mat	mat_identity(void);
t_mat	mat_ortho(t_vec min, t_vec max);

void	img_put(void *img, int x, int y, int color);
void	img_clear(void *img, int color);
void	img_line(void *img, t_vec from, t_vec to, int color);

#endif
