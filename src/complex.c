/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 01:07:02 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/01 20:42:39 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline t_compl	sum_complex(t_compl c1, t_compl c2)
{
	t_compl rez;

	rez.im = c1.im + c2.im;
	rez.re = c1.re + c2.re;
	return (rez);
}

inline static t_compl	mult_complex(t_compl c1, t_compl c2)
{
	t_compl rez;

	rez.im = c1.im * c2.re + c1.re * c2.im;
	rez.re = c1.re * c2.re - c1.im * c2.im;
	return (rez);
}

t_compl	pow_complex(t_compl c1, unsigned i)
{
	t_compl rez;
	int		j;

	if (i == 1)
		return (c1);
	rez = c1;
	j = 1;
	while (i > j)
	{
		if (i / 2 >= j)
		{
			rez = mult_complex(rez, rez);
			j *= 2;
		}
		else
		{
			rez = mult_complex(rez, c1);
			j++;
		}
	}
	return (rez);
}
