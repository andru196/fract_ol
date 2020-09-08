/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:06:37 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/09/09 01:26:27 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

# define WIDTH 1000
# define HEIGHT 1000
# define HYPOTENUSE 1415
# define PI 3.141592653589793238462643383279502884197169399375105820974944592

typedef struct s_line	t_line;
typedef struct s_point	t_point;
typedef unsigned char	byte;

struct	s_point
{
	double				x;
	double				y;
	double				z;
	int					origx;
	int					origy;
	int					origz;
	int					color;
	t_point				*next;
};

struct					s_line
{
	t_point				*p1;
	t_point				*p2;
	t_line				*next;
};

typedef struct			s_round
{
	t_point				*p;
	int					raduis;
	int					color;
}						t_round;

typedef struct			s_cont
{
	void				*mlx_ptr;
	void				*mlx_win;
	int					mouse_click[2];
	int					is_move;
}						t_cont;

typedef struct			s_compl
{
	double				re;
	double				im;
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


t_img					*new_image(void *mlx_ptr, int width, int height);
void					configure_events(t_cont *c);
int 					key_press(int keycode, void *param);
void					free_cont(t_cont *c);

t_compl					init_complex(double re, double im);
inline t_compl			sum_complex(t_compl c1, t_compl c2);
inline static t_compl	mult_complex(t_compl c1, t_compl c2);
t_compl					pow_complex(t_compl c1, unsigned i);



#endif