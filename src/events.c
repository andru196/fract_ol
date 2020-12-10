/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 23:23:07 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/12/10 21:25:13 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int			put_fractal(t_cont *c)
{
	char const	*setofset[] = {"Mandelbrot set", "julia set",
		"Burning Ship set", "Mandelbar set", "Dick set (my own)",
		"Face set (my own)", "Celtic Perpendicular set",
		"Perpendicular Mandelbrot set", "Perpendicular Burning Ship set"};

	mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
	mlx_string_put(c->mlx_ptr, c->mlx_win, WIDTH - 150, HEIGHT - 30,
		0xffffff, "Fract'ol by Sfalia-f");
	if (c->clcomponets.is_connected && c->current_set > 3)
		mlx_string_put(c->mlx_ptr, c->mlx_win, 55, 70,
		0xaaaaaa, "Chang thread mode (Press S)");
	mlx_string_put(c->mlx_ptr, c->mlx_win, WIDTH - 150, 50,
		0xaaaaaa, c->clcomponets.is_connected ? "Multy thread mode"
												: "Single thread mode");
	return (mlx_string_put(c->mlx_ptr, c->mlx_win, 50, 50, 0xaaaaaa,
										(char *)setofset[c->current_set - 1]));
}

void		configure_events(t_cont *c)
{
	mlx_hook(c->mlx_win, 2, (1L << 0), key_press, c);
	mlx_hook(c->mlx_win, 4, 1L << 2, mouse_press, c);
	mlx_hook(c->mlx_win, 6, (1L << 6), mouse_move, c);
}
