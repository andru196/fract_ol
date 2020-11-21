/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 23:23:07 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/21 20:06:32 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void		configure_events(t_cont *c)
{
	mlx_hook(c->mlx_win, 2, (1L << 0), key_press, c);
	mlx_hook(c->mlx_win, 4, 1L << 2, mouse_press, c);
	mlx_hook(c->mlx_win, 6, (1L << 6), mouse_move, c);
}
