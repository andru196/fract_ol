/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:58:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/10/27 00:53:12 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int		main(int argc, char **argv)
{
	t_cont	cont;
	t_img	*img;

	ft_bzero(&cont, sizeof(t_cont));
	if (!(cont.mlx_ptr = mlx_init()) ||
	!(cont.mlx_win = mlx_new_window(cont.mlx_ptr, WIDTH, HEIGHT, argv[1])))
		ft_putendl("Start failed!");
	configure_events(&cont);
	{

		img = new_image(cont.mlx_ptr, WIDTH, HEIGHT);
		cont.img = img;
		cont.maxiter = 10;
		cont.shift[1] = 0.0;
		cont.shift[0] = 0.0;
		ft_bzero(&cont.clcomponets, sizeof(t_clcomponents));
		stupid_fun(img, (cont.r =  2.0), cont.shift, cont.maxiter);
		mlx_put_image_to_window(cont.mlx_ptr, cont.mlx_win, img->img_ptr, 0, 0);
	}
	mlx_loop(cont.mlx_ptr);
	return (0);
}