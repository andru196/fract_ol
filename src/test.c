/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 23:19:25 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/10/29 00:37:58 by andru            ###   ########.fr       */
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

void	stupid_fun(t_cont *cont, double r, double shift[2], int max_iteration)
{
	t_compl min, max, c, factor, z;
	int red, green, blue, iteration, x, y;
	long double t;
	t_img *img;

	img = cont->img;
	int width, height;
	width = img->width;
	height = img->height;

	int *data = (int*)img->data;
	
	min.re = (-2.0L + shift[0]) * r;
	max.re = (2.0L + shift[0]) * r;
	min.im = (-2.0L + shift[1]) * r;
	max.im = (min.im + (max.re - min.re) * height / width);
	
	factor.re = (max.re - min.re) / (width - 1);
	factor.im = (max.im - min.im) / (height- 1);

	max_iteration += 200 * fabs(log(r));
	y = 0;
	while (y < height)
	{
		c.im = max.im - y * factor.im;
		x = 0;
		while (x < width)
		{
			c.re = min.re + x * factor.re;
			z = init_complex(c.re, c.im);
			iteration = 0;
			while ( iteration < max_iteration && (z.re * z.re + z.im * z.im) <= 4.0L)
			{
				z = init_complex(
					z.re * z.re - z.im * z.im + c.re,
					2.0L * z.re * z.im + c.im);
				iteration++;
			}
			t = (long double)iteration / (long double)max_iteration;
			int color;
			int red =  (int)(9 * (1 - t) * t * t * t * 255) << 16;
			int green = (int)(15 * (1 - t) * (1 - t) * t*t * 255) << 8;
			int blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
			color = red | green | blue;
			*data++ = (color);
			x++;
		}
		y++;
	}
}
