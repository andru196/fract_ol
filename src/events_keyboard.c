/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 00:40:44 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/10/28 01:29:06 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


static void	ext(t_cont *c)
{
	free_cont(c);
	ft_putendl("Bye, bye.....");
	exit(0);
}

int 		key_press(int keycode, void *param)
{
	t_cont *c;

	c = (t_cont*)param;
	if (113 == keycode || keycode == 65307) //65361
		ext(c);
	if (keycode == 65361) c->shift[0] -= DELTA;
	if (keycode == 65362) c->shift[1] += DELTA;
	if (keycode == 65363) c->shift[0] += DELTA;
	if (keycode == 65364) c->shift[1] -= DELTA;
	if (keycode == 65451 || keycode == 61) c->maxiter += 1000;
	if (keycode == 65453 || keycode == 45) c->maxiter -= 1000;

	if ((keycode >= 65361 && keycode <= 65364)
		|| keycode == 65453 || keycode == 65451)
	{
		stupid_fun(c, c->r, c->shift, c->maxiter);
		mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
	}
	return (1);
}
