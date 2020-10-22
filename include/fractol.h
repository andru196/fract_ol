/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:06:37 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/10/23 01:15:21 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <CL/cl.h>

# define WIDTH 1024
# define HEIGHT 1024
# define HYPOTENUSE 1415
# define PI 3.141592653589793238462643383279502884197169399375105820974944592
# define DELTA 1.5L
typedef struct s_line	t_line;
typedef struct s_point	t_point;
typedef unsigned char	byte;
typedef unsigned long long t_llu;


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

typedef struct	s_platform
{
	char		*profile;
	char		*version;
	char		*vendor;
	char		*extensions;
	char		*name;
}				t_platform_info;

typedef struct	s_device
{
	t_llu	type;
	t_llu	vendor_id;
	t_llu	max_compute_units;
	t_llu	max_work_item_dimensions;
	t_llu	max_work_group_size;
	size_t	*max_work_item_size;
	cl_uint	address_bits;
	t_llu	local_mem_size;
	t_llu	global_mem_size;
	char	available;
	char	*name;
	char	*vendor;
	char	*version;
	char	*profile;
	char	*extensions;
	char	*platform;
}			t_device_info;

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