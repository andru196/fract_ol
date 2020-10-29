/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 23:19:25 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/10/30 01:27:42 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline static t_compl	init_complex(double re, double im)
{
    t_compl	complex;
    
    complex.re = re;
    complex.im = im;
    return (complex);
}

inline static int get_color1(int iter, int maxiter)
{
	double	t;

	if (iter != maxiter)
	{
		t = (double)iter / maxiter;
		return  (~(int)(9 * (1 - t) * t * t * t * 255) << 16) ^
		(~(int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8) ^
		(~(int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255));
	}
	return (0);
}

static inline void	set_fractal(t_fract *f, double shift[2], t_img *img, double r)
{
	f->min.re = (-2.0L + shift[0]) * r;
	f->max.re = (2.0L + shift[0]) * r;
	f->min.im = (-2.0L + shift[1]) * r;
	f->max.im = (f->min.im + (f->max.re - f->min.re) * img->height / img->width);
	f->factor.re = (f->max.re - f->min.re) / (img->width - 1);
	f->factor.im = (f->max.im - f->min.im) / (img->height- 1);
}

void	mandelbrot_formula(int max_iteration, int *data, t_compl c, t_compl k)
{
	t_compl	z;
	int		iteration;

	k.re = 0;
	z = init_complex(c.re, c.im);
	iteration = 0;
	while (iteration < max_iteration && (z.re * z.re + z.im * z.im) <= 4.0L)
	{
		z = init_complex(
			z.re * z.re - z.im * z.im + c.re,
			2.0L * z.re * z.im + c.im);
		iteration++;
	}
	*data = get_color1(iteration, max_iteration);
}


void	julia_formula(int max_iteration, int *data, t_compl c, t_compl k)
{
	t_compl	z;
	int		iteration;

	z = init_complex(c.re, c.im);
	iteration = 0;
	while (iteration < max_iteration && (z.re * z.re + z.im * z.im) <= 4.0L)
	{
		z = init_complex(
			z.re * z.re - z.im * z.im - k.re,
			2.0L * z.re * z.im + k.im);
		iteration++;
	}
	*data = get_color1(iteration, max_iteration);
}

void	ship_formula(int max_iteration, int *data, t_compl c, t_compl k)
{
	t_compl	z;
	int		iteration;

	k.re = 0;
	z = init_complex(c.re, c.im);
	iteration = 0;
	while (iteration < max_iteration && (z.re * z.re + z.im * z.im) <= 4.0L)
	{
		z = init_complex(
			z.re * z.re - z.im * z.im - c.re,
			-2.0L * fabs( z.re * z.im) + c.im);
		iteration++;
	}
	*data = get_color1(iteration, max_iteration);
}

void	*get_formula(t_set current_set)
{
	if (current_set == mandelbrot_set)
		return (mandelbrot_formula);
	if (current_set == burningship_set)
		return (ship_formula);
	else 
		return (julia_formula);
}

void	stupid_fun_single_thread(t_cont *cont, double r, double shift[2], int max_iteration)
{
	t_compl c;
	t_fract f;
	int iteration, x, y;
	int width, height;
	int	*data;
	void(*formula)(int, int *, t_compl, t_compl);

	formula = get_formula(cont->current_set);
	width = cont->img->width;
	height = cont->img->height;

	set_fractal(&f, shift, cont->img, r);
	f.k = cont->k;
	max_iteration = 50 * fabs(log(r)) + max_iteration /
					(cont->current_set == julia_set ? 10 : 1);
	y = 0;
	data = (int*)cont->img->data;
	while (y < height)
	{
		c.im = f.max.im - y * f.factor.im;
		x = 0;
		while (x < width)
		{
			c.re = f.min.re + x * f.factor.re;
			formula(max_iteration, data++, c, f.k);
			x++;
		}
		y++;
	}
}
