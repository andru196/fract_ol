/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_funMac.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:44:20 by andru             #+#    #+#             */
/*   Updated: 2020/12/10 21:55:02 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			cl_release_all(t_clcomponents *comp)
{
	cl_int ret;

	ret = 0;
	if (comp->command_queue)
	{
		ret = clFlush(comp->command_queue);
		ret = clFinish(comp->command_queue);
		ret = clReleaseKernel(comp->kernel);
		ret = clReleaseProgram(comp->program);
		ret = clReleaseMemObject(comp->buffer);
		ret = clReleaseCommandQueue(comp->command_queue);
		ret = clReleaseContext(comp->context);
		comp->command_queue = NULL;
		comp->kernel = NULL;
		comp->program = NULL;
		comp->buffer = NULL;
		comp->context = NULL;
		if (ret >= 0)
			comp->is_connected = 0;
	}
	return (ret);
}

int			cl_read_img(t_clcomponents *comp, t_img *img)
{
	cl_int			ret;
	size_t const	global[] = {32, 32};
	size_t const	local[] = {(size_t)WIDTH, (size_t)HEIGHT};

	ret = clFlush(comp->command_queue);
	ret = clFinish(comp->command_queue);
	ret = clEnqueueNDRangeKernel(comp->command_queue, comp->kernel, 2, global,
												local, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(comp->command_queue, comp->buffer, CL_TRUE, 0,
							WIDTH * HEIGHT * sizeof(int), img->data, 0, 0, 0);
	return (!ret);
}

int			cl_set_param(t_clcomponents *comp, t_fract fract, t_img *img,
																int is_extra)
{
	unsigned	i;
	cl_int		ret;

	comp->buffer = clCreateBuffer(comp->context, CL_MEM_WRITE_ONLY,
					img->height * img->width * sizeof(cl_int4), NULL, &ret);
	i = 0;
	ret = clSetKernelArg(comp->kernel, i++, sizeof(cl_mem),
														(void *)&comp->buffer);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(int), &img->width);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(int), &img->height);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.min.re);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.min.im);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.max.re);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.max.im);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(int), &fract.iteration);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.factor.re);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.factor.im);
	if (is_extra)
	{
		ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.k.re);
		ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.k.im);
	}
	return (!ret);
}

int			cl_try_init_connect(t_clcomponents *c, char *filename,
																	t_set set)
{
	size_t	source_size;
	cl_int	ret;

	if (c->program_src || (ret = read_all_text(filename,
												&c->program_src)))
	{
		ret = clGetPlatformIDs(1, &c->platform_id, &c->ret_num_platforms);
		ret = clGetDeviceIDs(c->platform_id, CL_DEVICE_TYPE_GPU, 1,
									&c->device_id, &c->ret_num_devices);
		c->context = clCreateContext(NULL, 1, &c->device_id, 0, 0, &ret);
		c->command_queue = clCreateCommandQueue(c->context,
													c->device_id, 0, &ret);
		source_size = ft_strlen(c->program_src);
		c->program = clCreateProgramWithSource(c->context, 1,
											(const char **)&c->program_src,
								(const size_t *)&source_size, &ret);
		ret = clBuildProgram(c->program, 1, &c->device_id, 0, 0, 0);
		if (set == mandelbrot_set || set == julia_set)
			c->kernel = clCreateKernel(c->program, set == mandelbrot_set
												? MANDELBROT : JULIA, &ret);
		else
			c->kernel = clCreateKernel(c->program, BURNINGSHIP, &ret);
		c->is_connected = ret >= 0;
	}
	return (ret);
}
