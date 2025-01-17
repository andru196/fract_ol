/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:54:13 by andru             #+#    #+#             */
/*   Updated: 2020/12/10 20:56:20 by andru            ###   ########.fr       */
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
	double	t;

	if (iter != maxiter)
	{
		t = (double)iter / maxiter;
		return ((int)(9 * (1 - t) * t * t * t * 255) << 8) |
		((int)(15 * (1 - t) * (1 - t) * t * t * 255)) |
		((int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255) << 16);
	}
	return (0);
}

void					mandelbar_formula(int max_iteration, int *data,
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
			-2.0L * z.re * z.im + c.im);
		iteration++;
	}
	*data = get_color1(iteration, max_iteration);
}

void					cmandelbrot_formula(int max_iteration, int *data,
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
			z.re * z.re - z.im * z.im + (c.re),
			-2.0L * z.re * fabs(z.im) * z.im + c.im);
		iteration++;
	}
	*data = get_color1(iteration, max_iteration);
}

void					cmandelbar_formula(int max_iteration, int *data,
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
			z.re * z.re - z.im * z.im + fabs(c.re),
			-2.0L * z.re * fabs(z.im) * z.im - c.im);
		iteration++;
	}
	*data = get_color1(iteration, max_iteration);
}
