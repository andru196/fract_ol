/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:06:37 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/11/21 22:24:06 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# define WIDTH 1024
# define HEIGHT 1024
# define PI 3.141592653589793238462643383279502884197169399375105820974944592
# define DELTA 1.5L
# define DELTA_MAXITER 100
# include "cl_module.h"

typedef struct s_cont		t_cont;
typedef struct s_img		t_img;
typedef struct s_line		t_line;
typedef struct s_compl		t_compl;
typedef unsigned char		t_byte;
typedef unsigned long long	t_llu;
typedef struct s_fractol	t_fract;
typedef enum e_set			t_set;

enum				e_set
{
	mandelbrot_set = 1,
	julia_set = 2,
	burningship_set = 3
};

struct					s_compl
{
	double				re;
	double				im;
};

struct					s_img
{
	void				*img_ptr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_byte				*data;
	int					width;
	int					height;
};

struct					s_cont
{
	t_set				current_set;
	void				*mlx_ptr;
	void				*mlx_win;
	int					mouse_click[2];
	double				shift[2];
	double				r;
	int					is_move;
	int					maxiter;
	t_img				*img;
	t_compl				k;
	t_clcomponents		clcomponets;
	void				(*draw_fractal)(t_cont *, double, double[2],
											int);
};

struct					s_fractol
{
	t_compl				k;
	t_compl				factor;
	t_compl				max;
	t_compl				min;
	unsigned			iteration;
};

t_img					*new_image(void *mlx_ptr, int width, int height);
void					configure_events(t_cont *c);
void					free_cont(t_cont *c);
inline t_compl			sum_complex(t_compl c1, t_compl c2);
inline static t_compl	mult_complex(t_compl c1, t_compl c2);
t_compl					pow_complex(t_compl c1, unsigned i);
void					set_default(t_cont *c);

void					stupid_fun(t_cont *img, double r, double shift[2],
																	int mi);
void					stupid_fun_single_thread(t_cont *cont, double r,
										double shift[2], int max_iteration);
void					ship_formula(int max_iteration, int *data,
														t_compl c, t_compl k);
void					julia_formula(int max_iteration, int *data,
														t_compl c, t_compl k);
void					mandelbrot_formula(int max_iteration, int *data,
														t_compl c, t_compl k);

int						cl_read_img(t_clcomponents *comp, t_img *img);
int						cl_set_param(t_clcomponents *comp,
									t_fract fract, t_img *img, int is_extra);
int						cl_try_init_connect(t_clcomponents *comp,
													char *filename, t_set set);

#endif
