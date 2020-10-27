/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_fun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:44:20 by andru             #+#    #+#             */
/*   Updated: 2020/10/28 01:24:58 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	cl_release_all(t_clcomponents *comp)
{
	cl_int ret;

	ret = clFlush(comp->command_queue);
	ret = clFinish(comp->command_queue);
	ret = clReleaseKernel(comp->kernel);
	ret = clReleaseProgram(comp->program);
	ret = clReleaseMemObject(comp->buffer);
	ret = clReleaseCommandQueue(comp->command_queue);
	ret = clReleaseContext(comp->context);
	if (ret >= 0)
		comp->is_connected = 0;
	return (ret);
}

static inline void setcolor(int nums[WIDTH * HEIGHT], int maxiter, byte *img)
{
	double	t;
	int		color_rgb[4];

	for (int j = 0; j < WIDTH * HEIGHT; j++)
	{
		t = (double)nums[j] / maxiter;
		color_rgb[1] =  (int)(9 * (1 - t) * t * t * t * 255) << 16;
		color_rgb[2] = (int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8;
		color_rgb[3] = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		color_rgb[0] = color_rgb[1] | color_rgb[2] | color_rgb[3];
		((int*)img)[j] = color_rgb[0];
	}
}

int			cl_read_img(t_clcomponents *comp, t_img *img, int maxiter)
{
	unsigned int	i = 0;
	cl_int			ret;
	size_t const	global[] = {32, 32};
	size_t const	local[] = {(size_t) WIDTH, (size_t) HEIGHT};
	int				nums[HEIGHT * WIDTH];

	//bzero(nums, HEIGHT * WIDTH * sizeof(int));
	ret = clEnqueueNDRangeKernel(comp->command_queue, comp->kernel, 2, global,
												local, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(comp->command_queue, comp->buffer, CL_TRUE, 0,
							WIDTH * HEIGHT * sizeof(int), nums, 0, NULL, NULL);
	if (ret >= 0)
		setcolor(nums, maxiter, img->data);
	return (!ret);
}

int			cl_set_param(t_clcomponents *comp, t_fract fract, t_img *img, int maxiter)
{
	unsigned int i = 0;
	cl_int ret;

	comp->buffer = clCreateBuffer(comp->context, CL_MEM_WRITE_ONLY,
					img->height * img->width * sizeof(cl_int4), NULL, &ret);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(cl_mem),
														(void *)&comp->buffer);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(int), &img->width);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(int), &img->height);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.min_re);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.min_im);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.max_re);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.max_im);
	ret = clSetKernelArg(comp->kernel, i++, sizeof(int), &maxiter);
	return (!ret);
}

int			cl_try_init_connect(t_clcomponents *comp, char *filename)
{
	size_t	source_size;
	cl_int	ret;

	if ((ret = read_all_text(filename, &comp->program_src)))
	{
		ret = clGetPlatformIDs(1, &comp->platform_id, &comp->ret_num_platforms);
		ret = clGetDeviceIDs(comp->platform_id, CL_DEVICE_TYPE_GPU, 1, &comp->device_id, &comp->ret_num_devices);


		comp->context = clCreateContext(NULL, 1, &comp->device_id, NULL, NULL, &ret);
		comp->command_queue = clCreateCommandQueueWithProperties(comp->context, comp->device_id, 0, &ret);
		source_size = ft_strlen(comp->program_src);
		comp->program = clCreateProgramWithSource(comp->context, 1, (const char **)&comp->program_src,
											(const size_t *)&source_size, &ret);
		ret = clBuildProgram(comp->program, 1, &comp->device_id, NULL, NULL, NULL);
		////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////
		comp->kernel = clCreateKernel(comp->program, "mandelbrotProcess", &ret);
		if (ret >= 0)
			comp->is_connected = 1;
		////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////
	}
	return (ret);
}

t_platform_info *get_platform_info(cl_platform_id id)
{
    t_platform_info	*rez;
    size_t			size;

    rez = malloc(sizeof(t_platform_info));
    clGetPlatformInfo(id, CL_PLATFORM_PROFILE, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_PROFILE, size, (rez->profile = malloc(size)), &size);
    clGetPlatformInfo(id, CL_PLATFORM_VERSION, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_VERSION, size, (rez->version = malloc(size)), &size);
    clGetPlatformInfo(id, CL_PLATFORM_VENDOR, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_VENDOR, size, (rez->vendor = malloc(size)), &size);
    clGetPlatformInfo(id, CL_PLATFORM_EXTENSIONS, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_EXTENSIONS, size, (rez->extensions = malloc(size)), &size);
    clGetPlatformInfo(id, CL_PLATFORM_NAME, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_NAME, size, (rez->name = malloc(size)), &size);
	return rez;
}

t_device_info   *get_device_info(cl_device_id id)
{
    t_device_info	*rez;
    size_t			size;

	rez = malloc(sizeof(t_device_info));
	clGetDeviceInfo(id, CL_DEVICE_TYPE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_TYPE, sizeof(t_llu), &rez->type, &size);
	clGetDeviceInfo(id, CL_DEVICE_VENDOR_ID, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_VENDOR_ID, sizeof(t_llu), &rez->vendor_id, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_COMPUTE_UNITS, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(t_llu), &rez->max_compute_units, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(t_llu), &rez->max_work_item_dimensions, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_GROUP_SIZE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(t_llu), &rez->max_work_group_size, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_SIZES, size, rez->max_work_item_size = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_ADDRESS_BITS, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint), &rez->address_bits, &size);
	clGetDeviceInfo(id, CL_DEVICE_NAME, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_NAME, size, rez->name = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_VENDOR, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_VENDOR, size, rez->vendor = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_VERSION, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_VERSION, size, rez->version = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_PROFILE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_PROFILE, size, rez->profile = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_EXTENSIONS, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_EXTENSIONS, size, rez->extensions = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_PLATFORM, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_PLATFORM, size, rez->platform = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_LOCAL_MEM_SIZE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_LOCAL_MEM_SIZE, size, &rez->local_mem_size, &size);
	clGetDeviceInfo(id, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, size, &rez->global_mem_size, &size);
	clGetDeviceInfo(id, CL_DEVICE_AVAILABLE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_AVAILABLE, size, &rez->available, &size);
	return rez;
}
