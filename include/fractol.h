/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:06:37 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/09/12 01:54:08 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

# define WIDTH 300
# define HEIGHT 300
# define HYPOTENUSE 1415
# define PI 3.141592653589793238462643383279502884197169399375105820974944592
# define DELTA 1.5L
typedef struct s_line	t_line;
typedef struct s_point	t_point;
typedef unsigned char	byte;


typedef struct			s_compl
{
	double			re;
	double			im;
}						t_compl;

typedef struct			s_img
{
	void				*img_ptr;
	int 				bits_per_pixel;
	int 				size_line;
	int 				endian;
	byte				*data;
	int					width;
	int					height;
} 						t_img;

typedef struct			s_cont
{
	void				*mlx_ptr;
	void				*mlx_win;
	int					mouse_click[2];
	double				shift[2];
	double				r;
	int					is_move;
	int					maxiter;
	t_img				*img;
}						t_cont;


t_img					*new_image(void *mlx_ptr, int width, int height);
void					configure_events(t_cont *c);
int 					key_press(int keycode, void *param);
void					free_cont(t_cont *c);

//t_compl					init_complex(double re, double im);
inline t_compl			sum_complex(t_compl c1, t_compl c2);
inline static t_compl	mult_complex(t_compl c1, t_compl c2);
t_compl					pow_complex(t_compl c1, unsigned i);

void					stupid_fun(t_img *img, double r, double shift[2], int mi);


#endif