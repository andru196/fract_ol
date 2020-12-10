/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:58:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/12/10 21:48:42 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	print_usage(char const *setofset[])
{
	ft_printf("Usage: ./fractol [%s|%s|%s|%s|%s|%s|%s|%s|%s]\n", setofset[0],
		setofset[1], setofset[2], setofset[3], setofset[4], setofset[5],
		setofset[6], setofset[7], setofset[8]);
	return (1);
}

int			main(int argc, char **argv)
{
	t_cont		cont;
	t_img		*img;
	size_t		set;
	char const	*setofset[] = {"mandelbrot", "julia", "ship", "mandelbar",
		"dick", "face", "celtic_perpendicular",
		"perpendicular_mandelbrot", "perpendicular_burningship"};

	if (argc != 2 || !(set = (ft_acontainstr(argv[1], (char **)setofset, 9))))
		return (print_usage(setofset));
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
	put_fractal(&cont);
	mlx_loop(cont.mlx_ptr);
	return (0);
}
