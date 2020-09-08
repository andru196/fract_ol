/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:40:56 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/09/09 00:07:22 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img	*new_image(void *mlx_ptr, int width, int height)
{
	t_img	*rez;

	rez = malloc(sizeof(t_img));
	if (rez)
	{
		rez->img_ptr = mlx_new_image(mlx_ptr, width, height);
		if (!rez->img_ptr)
		{
			free(rez);
			return (NULL);
		}
		rez->width = width;
		rez->height = height;
		rez->data = (byte *)(mlx_get_data_addr(rez->img_ptr,
			&rez->bits_per_pixel,
			&rez->size_line,
			&rez->endian));
	}
	return (rez);
}
