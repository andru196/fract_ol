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

static int	mouse_press(int button, int x, int y, void *param)
{
	t_cont *c;

	c = param;
	if (button == 4)
		c->r *= 19.0 / 20.0;
	else if (button == 5)
		c->r /= 19.0 / 20.0;
	if (button == 5 || button == 4)
	{
		c->shift[0] += (((double)x/WIDTH - 0.5) * (c->r >= 0 ? 1 : -1)) / (c->r); //((double)x/WIDTH - 0.5) > 0 ? (-c->r) / 20 : c->r / 20;
		c->shift[1] += (((double)y/HEIGHT - 0.5) * (c->r >= 0 ? -1 : 1)) / (c->r);//((double)y/HEIGHT - 0.5) > 0 ? (-c->r) / 20 : c->r / 20;
		stupid_fun(c->img, (c->r), c->shift);
		mlx_clear_window(c->mlx_ptr, c->mlx_win);
		mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
	}
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
