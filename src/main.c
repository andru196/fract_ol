/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:58:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/09/11 23:56:06 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int		main(int argc, char **argv)
{
	t_cont	cont;

	ft_bzero(&cont, sizeof(t_cont));
	if (!(cont.mlx_ptr = mlx_init()) ||
	!(cont.mlx_win = mlx_new_window(cont.mlx_ptr, WIDTH, HEIGHT, argv[1])))
		printf("Start failed!");
	configure_events(&cont);
	{
		t_img	*img;
	
		img = new_image(cont.mlx_ptr, WIDTH, HEIGHT);
		cont.img = img;
		cont.maxiter = 10;
		cont.shift[1] = 0.0;
		cont.shift[0] = 0.0;
		stupid_fun(img, (cont.r =  2.0), cont.shift, cont.maxiter);
		mlx_put_image_to_window(cont.mlx_ptr, cont.mlx_win, img->img_ptr, 0, 0);

	}
	mlx_loop(cont.mlx_ptr);
	//free_cont(&cont);
	return (0);
}