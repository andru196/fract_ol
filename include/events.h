/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 22:03:58 by andru             #+#    #+#             */
/*   Updated: 2020/11/21 22:01:39 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H
# include "fractol.h"

void		lr_mouse_press(int button, int x, int y, t_cont *c);
int			mouse_press(int button, int x, int y, void *param);
int			mouse_release(int button, int x, int y, void *param);
int			mouse_move(int x, int y, void *param);
int			key_press(int keycode, void *param);

#endif
