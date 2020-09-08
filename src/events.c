/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 23:23:07 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/09/09 01:02:08 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mouse_press(int button, int x, int y, void *param)
{
	t_cont *c;

	c = param;
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
