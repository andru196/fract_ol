/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 23:19:25 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/09/13 23:48:30 by sfalia-f         ###   ########.fr       */
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

void	stupid_fun(t_img *img, double r, double shift[2])
{
	t_compl min, max, c, factor, z;
	int max_iteration, red, green, blue, iteration, x, y;
	long double t;

	int width, height;
	width = img->width;
	height = img->height;

	int *data = img->data;
	
	min.re = (-2.0L + shift[0]) * r;
	max.re = (2.0L + shift[0]) * r;
	min.im = (-2.0L + shift[1]) * r;
	max.im = (min.im + (max.re - min.re) * height / width);
	
	factor.re = (max.re - min.re) / (width - 1);
	factor.im = (max.im - min.im) / (height- 1);

	max_iteration = 70 - 150 * log10(r);
	printf("maxit:%d\n", max_iteration);
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
					2.0 * z.re * z.im + c.im);
				iteration++;
			}
			t = (long double)iteration / (long double)max_iteration;
			int color;
			//if (iteration != max_iteration)
			//{
				int red =  (int)(9 * (1 - t) * t*t*t * 255) << 16;
				int green = (int)(15 * (1 - t)* (1 - t) * t*t * 255) << 8;
				int blue = (int)(8.5 * (1 - t)*(1 - t)*(1 - t) * t * 255);
				color = red | green | blue;
			//}
			//else
			//	color = 0;
			*data++ = (color);
			x++;
		}
		y++;
	}
	printf("%lf %lf %lf log10(r):%lf\n", r, shift[0], shift[1], log10(r) * 150.0);
}
