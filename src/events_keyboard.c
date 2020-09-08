/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 00:40:44 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/09/09 01:04:00 by sfalia-f         ###   ########.fr       */
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
	if (113 == keycode || keycode == 65307)
		ext(c);
	return (1);
}
