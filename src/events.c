/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 23:23:07 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/09/13 23:47:39 by sfalia-f         ###   ########.fr       */
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
	stupid_fun(c->img, (c->r), c->shift, c->maxiter);
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
		stupid_fun(c->img, (c->r), c->shift, c->maxiter);
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

static int	mouse_move(int x, int y, void *param)
{
	t_cont	*c;
	
	c = param;
	return (1);
}

void		configure_events(t_cont *c)
{
	mlx_hook(c->mlx_win, 2, (1L<<0), key_press, c);
	mlx_hook(c->mlx_win, 4, 1L<<2, mouse_press, c);
	mlx_hook(c->mlx_win, 5, (1L<<3), mouse_release, c);
	mlx_hook(c->mlx_win, 6, (1L<<6), mouse_move, c);
}
