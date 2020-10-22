/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:42:30 by andru             #+#    #+#             */
/*   Updated: 2020/10/23 01:24:38 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MEM_SIZE (1024)
#define MAX_SOURCE_SIZE (16000)

void    try_mult(int maxiter, double fromX, double fromY, double toX, double toY, byte *img, size_t size)
{
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem memobj = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;
	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;
	
	char string[MEM_SIZE];
	
	FILE *fp;
	char fileName[] = "./hello.cl";
	char *source_str;
	size_t source_size;

	/* Load the source code containing the kernel*/
	fp = fopen(fileName, "r");
	if (!fp) {
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	/* Get Platform and Device Info */
	ret = clGetPlatformIDs(NULL, NULL, &ret_num_platforms);
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	
	t_platform_info *platform = NULL;
	if (ret != -1001)
		platform = get_platform_info(platform_id);

	ret = clGetDeviceIDs(0, CL_DEVICE_TYPE_ALL, 0, 0, &ret_num_devices);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);
	char str[100];

	t_device_info *device = get_device_info(device_id);

	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	/* Create Command Queue */
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

	/* Create Memory Buffer */

	/* Create Kernel Program from the source */
	program = clCreateProgramWithSource(context, 1, (const char **)&source_str,
	(const size_t *)&source_size, &ret);
	
	/* Build Kernel Program */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	/* Create OpenCL Kernel */
	kernel = clCreateKernel(program, "mandelbrotProcess", &ret);

	/* Set OpenCL Kernel Parameters */
	int width = (int) WIDTH;
	int height = (int) HEIGHT;
	

	unsigned int i = 0;

	cl_mem buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size * sizeof(cl_int4), NULL, &ret);

	ret = clSetKernelArg(kernel, i++, sizeof(cl_mem), (void *)&buffer);
	ret = clSetKernelArg(kernel, i++, sizeof(int), &width);
	ret = clSetKernelArg(kernel, i++, sizeof(int), &height);
	ret = clSetKernelArg(kernel, i++, sizeof(double), &fromX);
	ret = clSetKernelArg(kernel, i++, sizeof(double), &fromY);
	ret = clSetKernelArg(kernel, i++, sizeof(double), &toX);
	ret = clSetKernelArg(kernel, i++, sizeof(double), &toY);
	ret = clSetKernelArg(kernel, i++, sizeof(int), &maxiter);

	/* Execute OpenCL Kernel */
	//ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	size_t global[] = {32, 32};
	size_t local[] = {(size_t) WIDTH, (size_t) HEIGHT};
	
	
	int nums[size];
	bzero(nums, size * sizeof(int));

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, global, local, NULL, 0, NULL, NULL);
	

	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0,
	width * height * sizeof(int),nums, 0, NULL, NULL);

	/* Display Result */

	/* Finalization */
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(buffer);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	for (int j = 0; j < size; j++)
	{
		double t = (double)nums[j] / maxiter;
		int color;
		int red =  (int)(9 * (1 - t) * t * t * t * 255) << 16;
		int green = (int)(15 * (1 - t) * (1 - t) * t*t * 255) << 8;
		int blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		color = red | green | blue;
		((int*)img)[j] = color;
	}
	free(source_str);
	
}



void	stupid_fun(t_img *img, double r, double shift[2], int max_iteration)
{
	t_compl min, max, c, factor, z;
	long double t;

	int width, height;
	width = img->width;
	height = img->height;

	int *data = img->data;
	
	min.re = (-2.0L + shift[0]) * r;
	max.re = (2.0L + shift[0]) * r;
	min.im = (-2.0L + shift[1]) * r;
	max.im = (min.im + (max.re - min.re) * height / width);
	
	factor.re = (max.re - min.re) / (width - 1);
	factor.im = (max.im - min.im) / (height- 1);

	max_iteration += 200 * fabs(log(r));
	try_mult(max_iteration, min.re, min.im, max.re,  max.im, img->data, img->height * img->width);
}
