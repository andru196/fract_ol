/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:58:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/09/09 01:03:06 by sfalia-f         ###   ########.fr       */
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
	
		img = new_image(cont.mlx_ptr, 800, 700);
		for (int y = 0; y < img->size_line * img->height; y++)
		{
			img->data[y] = 0xff & (y >> (y % 16));
		}
		mlx_put_image_to_window(cont.mlx_ptr, cont.mlx_win, img->img_ptr, 100, 100);

	}
	mlx_loop(cont.mlx_ptr);
	//free_cont(&cont);
	return (0);
}