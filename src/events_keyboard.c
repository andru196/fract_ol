/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 00:40:44 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/12/10 21:08:47 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "keys.h"

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
		put_fractal(c);
	}
	return (keycode == ARROW_L || keycode == ARROW_U || keycode == ARROW_R ||
		keycode == ARROW_D || keycode == NUM_PLUS || keycode == 61 ||
		keycode == NUM_MINS || keycode == 45);
}

static inline t_set	choose_set(int keycode)
{
	if (keycode == NUM_1)
		return (mandelbrot_set);
	else if (keycode == NUM_2)
		return (burningship_set);
	else if (keycode == NUM_3)
		return (julia_set);
	else if (keycode == NUM_4)
		return (mandelbar);
	else if (keycode == NUM_5)
		return (celtic_mandelbrot);
	else if (keycode == NUM_6)
		return (celtic_mandelbar);
	else if (keycode == NUM_7)
		return (celtic_perpendicular);
	else if (keycode == NUM_8)
		return (perpendicular_mandelbrot);
	else
		return (perpendicular_burningship);
}

static inline int	change_set(t_cont *c, int keycode)
{
	t_set curent;

	if (keycode == NUM_1 || keycode == NUM_2 || keycode == NUM_3
		|| keycode == NUM_4 || keycode == NUM_5 || keycode == NUM_6
		|| keycode == NUM_7 || keycode == NUM_8 || keycode == NUM_9)
	{
		if (c->draw_fractal == stupid_fun)
			cl_release_all(&c->clcomponets);
		curent = choose_set(keycode);
		if (c->current_set != curent)
			c->current_set = curent;
		set_default(c);
		mlx_clear_window(c->mlx_ptr, c->mlx_win);
		c->draw_fractal(c, c->r, c->shift, c->maxiter);
		put_fractal(c);
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
		put_fractal(c);
		return (1);
	}
	return (0);
}

int					key_press(int keycode, void *param)
{
	t_cont *c;

	c = (t_cont*)param;
	if (NUM_Q == keycode || keycode == NUM_ESC)
	{
		free_cont(c);
		ft_putendl("Bye, bye.....");
		exit(0);
	}
	if (deltas(c, keycode))
		;
	else if (change_set(c, keycode))
		;
	else if (change_mod(c, keycode))
		;
	return (1);
}
