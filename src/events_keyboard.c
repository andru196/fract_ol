/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 00:40:44 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/21 20:32:16 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "keys.h"

static void			ext(t_cont *c)
{
	free_cont(c);
	ft_putendl("Bye, bye.....");
	exit(0);
}

static inline int	deltas(t_cont *c, int keycode)
{
	if (keycode == ARROW_L)
		c->shift[0] -= DELTA;
	else if (keycode == ARROW_U)
		c->shift[1] += DELTA;
	else if (keycode == ARROW_R)
		c->shift[0] += DELTA;
	else if (keycode == ARROW_D)
		c->shift[1] -= DELTA;
	else if (keycode == NUM_PLUS || keycode == 61)
		c->maxiter += DELTA_MAXITER;
	else if (keycode == NUM_MINS || keycode == 45)
		c->maxiter -= DELTA_MAXITER;
	if ((keycode >= ARROW_L && keycode <= ARROW_D)
		|| keycode == NUM_PLUS || keycode == NUM_MINS)
	{
		c->draw_fractal(c, c->r, c->shift, c->maxiter);
		mlx_clear_window(c->mlx_ptr, c->mlx_win);
		mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
	}
	return (keycode == ARROW_L || keycode == ARROW_U || keycode == ARROW_R ||
		keycode == ARROW_D || keycode == NUM_PLUS || keycode == 61 ||
		keycode == NUM_MINS || keycode == 45);
}

static inline int	change_set(t_cont *c, int keycode)
{
	if (keycode == NUM_1 || keycode == NUM_2 || keycode == NUM_3)
	{
		if (c->draw_fractal == stupid_fun)
			cl_release_all(&c->clcomponets);
		if (keycode == NUM_1 && c->current_set != mandelbrot_set)
			c->current_set = mandelbrot_set;
		else if (keycode == NUM_2 && c->current_set != burningship_set)
			c->current_set = burningship_set;
		else if (keycode == NUM_3 && c->current_set != julia_set)
			c->current_set = julia_set;
		set_default(c);
		mlx_clear_window(c->mlx_ptr, c->mlx_win);
		c->draw_fractal(c, c->r, c->shift, c->maxiter);
		mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
		return (1);
	}
	return (0);
}

inline static int	change_mod(t_cont *c, int keycode)
{
	if (keycode == NUM_S)
	{
		(c->draw_fractal = c->draw_fractal != stupid_fun ? stupid_fun :
			stupid_fun_single_thread)(c, c->r, c->shift, c->maxiter);
		if (c->draw_fractal == stupid_fun_single_thread)
			cl_release_all(&c->clcomponets);
		mlx_clear_window(c->mlx_ptr, c->mlx_win);
		mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
		return (1);
	}
	return (0);
}

int					key_press(int keycode, void *param)
{
	t_cont *c;

	c = (t_cont*)param;
	if (NUM_Q == keycode || keycode == NUM_ESC)
		ext(c);
	if (deltas(c, keycode))
		;
	else if (change_set(c, keycode))
		;
	else if (change_mod(c, keycode))
		;
	return (1);
}
