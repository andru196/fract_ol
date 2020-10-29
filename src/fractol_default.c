/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_default.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 23:38:35 by andru             #+#    #+#             */
/*   Updated: 2020/10/29 23:43:36 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline static t_compl	init_complex(double re, double im)
{
    t_compl	complex;
    
    complex.re = re;
    complex.im = im;
    return (complex);
}

void    set_default(t_cont *c)
{
    c->maxiter = 40;
    c->k = init_complex(-0.4, 0.6);
    c->r = 2.0;
    ft_bzero(c->shift, sizeof(double) * 2);
}
