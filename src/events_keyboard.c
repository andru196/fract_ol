/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 00:40:44 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/09/13 23:32:34 by sfalia-f         ###   ########.fr       */
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
	if (keycode >= 65361 && keycode <= 65364)
	{
		t_img *img = new_image(c->mlx_ptr, WIDTH, HEIGHT);
		stupid_fun(img, c->r, c->shift);
		c->img = img;
		mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
	}
	return (1);
}
