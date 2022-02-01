/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 14:20:27 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/02/01 08:21:55 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stddef.h>

typedef struct s_vec	t_vec;
typedef struct s_mat	t_mat;
typedef struct s_fdf	t_fdf;
typedef struct s_vert	t_vert;

struct s_vec
{
	float	el[4];
};

struct s_mat
{
	t_vec	el[4];
};

struct s_vert
{
	t_vec	pos;
	t_vec	col;
	t_vec	map_col;
	int		height;
};

struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	t_vert	*map;
	char	*color;
	float	*depth;
	int		win_width;
	int		win_height;
	size_t	map_width;
	size_t	map_height;
	int		min;
	int		max;
	t_vec	translate;
	t_vec	scale;
	t_vec	rotate;
	int		mouse_1_down;
	int		mouse_2_down;
	int		mouse_x;
	int		mouse_y;
	int		use_persp;
	int		use_fog;
	int		color_mode;
	int		draw_mode;
};

t_vec	mat_column(t_mat lhs, int rhs);
t_mat	mat_transpose(t_mat lhs);
float	mul_vv(t_vec lhs, t_vec rhs);
t_vec	mul_vm(t_vec lhs, t_mat rhs);
t_mat	mul_mm(t_mat lhs, t_mat rhs);

t_mat	mat_translate(t_vec	v);
t_mat	mat_scale(t_vec v);
t_mat	mat_rotate_x(float v);
t_mat	mat_rotate_y(float v);
t_mat	mat_rotate_z(float v);

t_vec	vec_new(float x, float y, float z, float w);
t_vec	vec_add(t_vec lhs, t_vec rhs);
t_vec	vec_sub(t_vec lhs, t_vec rhs);
t_vec	vec_scale(t_vec lhs, float rhs);

t_mat	mat_new(t_vec x, t_vec y, t_vec z, t_vec w);
t_mat	mat_identity(void);
t_mat	mat_ortho(t_vec min, t_vec max);
t_mat	mat_persp(t_vec min, t_vec max);

void	img_put(t_fdf *fdf, t_vec pos, t_vec col);
void	img_clear(t_fdf *fdf, t_vec col);
void	img_line(t_fdf *fdf, t_vert from, t_vert to);

t_vec	clip_convert(t_fdf *fdf, t_vec vec);
void	clip_line(t_fdf *fdf, t_vert from, t_vert to);
int		clip(t_vec vec);
void	fdf_assert(int condition, const char *message);
t_vert	*fdf_read(size_t *width, size_t *height, const char *filename);
void	fdf_render(t_fdf *fdf);

int		close_hook(t_fdf *fdf);
int		key_down_hook(int keycode, t_fdf *fdf);
int		key_up_hook(int keycode, t_fdf *fdf);
int		mouse_down_hook(int button, int x, int y, t_fdf *fdf);
int		mouse_up_hook(int button, int x, int y, t_fdf *fdf);
int		mouse_moved_hook(int x, int y, t_fdf *fdf);

#endif
