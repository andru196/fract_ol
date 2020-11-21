/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:58:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/21 21:52:43 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char **argv)
{
	t_cont		cont;
	t_img		*img;
	size_t		set;
	char const	*setofset[] = {"mandelbrot", "julia", "ship"};

	if (argc != 2 || !(set = (ft_acontainstr(argv[1], (char **)setofset, 3))))
		return (ft_printf("Usage: ./fractol [mandelbrot|ship|julia]\n") || 1);
	ft_bzero(&cont, sizeof(t_cont));
	cont.current_set = set;
	if (!(cont.mlx_ptr = mlx_init()) ||
	!(cont.mlx_win = mlx_new_window(cont.mlx_ptr, WIDTH, HEIGHT, argv[1])))
		ft_putendl("Start failed!");
	configure_events(&cont);
	img = new_image(cont.mlx_ptr, WIDTH, HEIGHT);
	cont.img = img;
	set_default(&cont);
	(cont.draw_fractal = stupid_fun)(&cont, cont.r, cont.shift, cont.maxiter);
	mlx_put_image_to_window(cont.mlx_ptr, cont.mlx_win, img->img_ptr, 0, 0);
	mlx_loop(cont.mlx_ptr);
	return (0);
}
