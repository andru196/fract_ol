/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:54:13 by andru             #+#    #+#             */
/*   Updated: 2020/12/09 02:20:15 by andru            ###   ########.fr       */
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

inline static int		get_color1(int iter, int maxiter)
{
	double			t;
	static short	back = 1;
	
	if (iter != maxiter)
	{
		t = (double)iter / maxiter;
		return ((int)(9 * (1 - t) * t * t * t * 255)) |
		((int)(10 * (1 - t) * (1 - t) * t * t * 255) << 16) |
		((int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255) << 8);
	}
	back = (back + 1) * (back - 1000) & 0xaefa;
	return ((back) << 8);
}

void					cperpendicular_formula(int max_iteration, int *data,
														t_compl c, t_compl k)
{
	t_compl	z;
	int		iteration;

	k.re = 0;
	z = init_complex(c.re, c.im);
	iteration = 0;
	while (iteration < max_iteration && (z.re * z.re + z.im * z.im) <= 4.0L)
	{
		z = init_complex(
			fabs(z.re * z.re - z.im * z.im) + c.re,
			-2.0L * fabs(z.re) * z.im + c.im);
		iteration++;
	}
	*data = get_color1(iteration, max_iteration);
}

void					pmandelbrot_formula(int max_iteration, int *data,
														t_compl c, t_compl k)
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
			-2.0L * fabs(z.re) * z.im + c.im);
		iteration++;
	}
	*data = get_color1(iteration, max_iteration);
}

void					pship_formula(int max_iteration, int *data,
														t_compl c, t_compl k)
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
			-2.0L * z.re * fabs(z.im) + c.im);
		iteration++;
	}
	*data = get_color1(iteration, max_iteration);
}
