/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:06:37 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/10/28 01:05:05 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# define WIDTH 1024
# define HEIGHT 1024
# define PI 3.141592653589793238462643383279502884197169399375105820974944592
# define DELTA 1.5L

typedef struct s_cont		t_cont;
typedef struct s_img		t_img;
typedef struct s_line		t_line;
typedef struct s_compl		t_compl;
typedef struct s_point		t_point;
typedef unsigned char		byte;
typedef unsigned long long	t_llu;
typedef struct s_fractol	t_fract;

# include "cl_module.h"

struct					s_compl
{
	double				re;
	double				im;
};

struct					s_img
{
	void				*img_ptr;
	int 				bits_per_pixel;
	int 				size_line;
	int 				endian;
	byte				*data;
	int					width;
	int					height;
};

struct					s_cont
{
	void				*mlx_ptr;
	void				*mlx_win;
	int					mouse_click[2];
	double				shift[2];
	double				r;
	int					is_move;
	int					maxiter;
	t_img				*img;
	t_clcomponents		clcomponets;
};


struct					s_fractol
{
	double				max_re;
	double				max_im;
	double				min_re;
	double				min_im;
	unsigned			iteration;
};

t_img					*new_image(void *mlx_ptr, int width, int height);
void					configure_events(t_cont *c);
int 					key_press(int keycode, void *param);
void					free_cont(t_cont *c);

//t_compl					init_complex(double re, double im);
inline t_compl			sum_complex(t_compl c1, t_compl c2);
inline static t_compl	mult_complex(t_compl c1, t_compl c2);
t_compl					pow_complex(t_compl c1, unsigned i);

void					stupid_fun(t_cont *img, double r, double shift[2], int mi);


#endif