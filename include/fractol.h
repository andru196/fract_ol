/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:06:37 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/09/07 21:32:20 by sfalia-f         ###   ########.fr       */
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

typedef struct			s_map
{
	int					x;
	int					y;
	int					z_max;
	int					z_min;
	float				radx;
	float				rady;
	float				radz;
	t_point				*points;
	t_line				*lines;
}						t_map;

typedef struct			s_cont
{
	void				*mlx_ptr;
	void				*mlx_win;
	t_map				*map;
	int					mouse_click[2];
	int					is_move;
}						t_cont;

#endif