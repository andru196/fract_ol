/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 23:23:07 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/10/30 00:20:01 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	lr_mouse_press(int button, int x, int y, t_cont *c)
{
	long double mult;

	mult = button == 1 ? 1.0L / 3.0 :  3.0;
	if (button == 1)
	{
		c->shift[0] += 4*((double)x/WIDTH - 0.5) ; 
		c->shift[1] += -4*((double)y/HEIGHT - 0.5) ;
	}
	c->shift[0] /= mult;
	c->shift[1] /= mult;
	c->r *= mult;
	c->draw_fractal(c, (c->r), c->shift, c->maxiter);
	mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
}

static int	mouse_press(int button, int x, int y, void *param)
{
	t_cont		*c;
	long double mult;
	static int	falg = 1;

	falg = button == 2 ? !falg : falg;
	if (button == 5 || button == 4)
	{
		c = param;
		mult = button == 4 ? 15.0 / 20.0 :  20.0 / 15.0;
		if (falg && button == 4)
		{
			c->shift[0] += ((double)x/WIDTH - 0.5) * 4;
			c->shift[1] += -((double)y/HEIGHT - 0.5) * 4;
		}
		c->shift[0] /= mult;
		c->shift[1] /= mult;
		c->r *= mult;
		c->draw_fractal(c, (c->r), c->shift, c->maxiter);
		mlx_clear_window(c->mlx_ptr, c->mlx_win);
		mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
	}
	else if (button == 1 || button == 3)
		lr_mouse_press(button, x, y, param);
	return (1);
}

static int	mouse_release(int button, int x, int y, void *param)
{
	t_cont	*c;

	c = param;
	return (1);
}

inline static t_compl	init_complex(double re, double im)
{
    t_compl	complex;
    
    complex.re = re;
    complex.im = im;
    return (complex);
}

static int	mouse_move(int x, int y, void *param)
{
	t_cont	*c;
	
	c = param;
	if (c->current_set == julia_set)
	{
		c->k = init_complex(
			4 * ((double)x / WIDTH - 0.5),
			4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		if (x % 8 == 0 || y % 8 == 0)
		{
			c->draw_fractal(c, (c->r), c->shift, 50);
			mlx_clear_window(c->mlx_ptr, c->mlx_win);
			mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
		}
		return (0);
	}
	return (1);
}

void		configure_events(t_cont *c)
{
	mlx_hook(c->mlx_win, 2, (1L<<0), key_press, c);
	mlx_hook(c->mlx_win, 4, 1L<<2, mouse_press, c);
	mlx_hook(c->mlx_win, 5, (1L<<3), mouse_release, c);
	mlx_hook(c->mlx_win, 6, (1L<<6), mouse_move, c);
}
