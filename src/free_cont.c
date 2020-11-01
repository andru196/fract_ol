/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cont.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 01:04:41 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/01 22:15:47 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	free_cont(t_cont *c)
{
	if (c)
	{
		if (c->img)
		{
			if (c->img->data)
				mlx_destroy_image(c->mlx_ptr, c->img->img_ptr);
			ft_memdel((void **)&c->img);
		}
		if (c->mlx_win)
			mlx_destroy_window(c->mlx_ptr, c->mlx_win);
		if (c->mlx_ptr)
			free((void *)c->mlx_ptr);
		cl_release_all(&c->clcomponets);
		ft_memdel((void **)&c->clcomponets.program_src);
	}
}
