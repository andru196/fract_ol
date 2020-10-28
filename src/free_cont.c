/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cont.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 01:04:41 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/10/28 23:19:29 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	free_cont(t_cont *c)
{
	t_point	*p;
	t_point	*tmp;

	if (c)
	{
		if (c->mlx_win)
			mlx_destroy_window(c->mlx_ptr, c->mlx_win);
		if (c->mlx_ptr)
			free(c->mlx_ptr);
		cl_release_all(&c->clcomponets);
	}
}
