/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:13:39 by majosue           #+#    #+#             */
/*   Updated: 2020/03/13 14:50:48 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_read_cl_program(t_mlx *mlx)
{
	FILE	*fp;
	size_t	source_size;
	char	*source_str;

	fp = fopen("computer.cl", "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	source_str = (char *)malloc(MAX_SOURCE_SIZE);
	if (!source_str)
	{
		ft_putendl("Error");
		exit(1);
	}
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
	mlx->cl.program = clCreateProgramWithSource(mlx->cl.context,\
	1, (const char **)&source_str, (const size_t *)&source_size, &mlx->cl.ret);
	mlx->cl.ret = clBuildProgram(mlx->cl.program, 1,\
	&mlx->cl.device_id, "-I ./", NULL, NULL);
	free(source_str);
}

void	ft_opencl_init_path1(t_mlx *mlx)
{
	mlx->cl.platform_id = NULL;
	mlx->cl.device_id = NULL;
	mlx->cl.ret = clGetPlatformIDs(1, &mlx->cl.platform_id,
	&mlx->cl.ret_num_platforms);
	mlx->cl.ret = clGetDeviceIDs(mlx->cl.platform_id, CL_DEVICE_TYPE_GPU,
	1, &mlx->cl.device_id, &mlx->cl.ret_num_devices);
	mlx->cl.context = clCreateContext(NULL, 1, &mlx->cl.device_id, NULL,
	NULL, &mlx->cl.ret);
	mlx->cl.command_queue = clCreateCommandQueue(mlx->cl.context,
	mlx->cl.device_id, 0, &mlx->cl.ret);
	mlx->cl.re_mem_obj = clCreateBuffer(mlx->cl.context, CL_MEM_READ_ONLY,
	mlx->n * sizeof(double), NULL, &mlx->cl.ret);
	mlx->cl.control_mem_obj = clCreateBuffer(mlx->cl.context, CL_MEM_READ_ONLY,\
	sizeof(t_control), NULL, &mlx->cl.ret);
	mlx->cl.im_mem_obj = clCreateBuffer(mlx->cl.context, CL_MEM_READ_ONLY,\
	mlx->n * sizeof(double), NULL, &mlx->cl.ret);
	mlx->cl.color_mem_obj = clCreateBuffer(mlx->cl.context, CL_MEM_WRITE_ONLY,\
	mlx->n * sizeof(int), NULL, &mlx->cl.ret);
}

void	ft_cl_buffers_eq(t_mlx *mlx)
{
	mlx->cl.ret = clEnqueueWriteBuffer(mlx->cl.command_queue,\
	mlx->cl.re_mem_obj, CL_TRUE, 0, mlx->n * sizeof(double),\
	mlx->re, 0, NULL, NULL);
	mlx->cl.ret = clEnqueueWriteBuffer(mlx->cl.command_queue,\
	mlx->cl.im_mem_obj, CL_TRUE, 0, mlx->n * sizeof(double),\
	mlx->im, 0, NULL, NULL);
	mlx->cl.ret = clEnqueueWriteBuffer(mlx->cl.command_queue,\
	mlx->cl.control_mem_obj, CL_TRUE, 0, sizeof(t_control),\
	&mlx->control, 0, NULL, NULL);
}

void	ft_cl_kernels_create(t_mlx *mlx)
{
	mlx->cl.kernel[0] = clCreateKernel(mlx->cl.program, "mandelbrot",\
	&mlx->cl.ret);
	mlx->cl.kernel[1] = clCreateKernel(mlx->cl.program, "julia", &mlx->cl.ret);
	mlx->cl.kernel[2] = clCreateKernel(mlx->cl.program, "newton",\
	&mlx->cl.ret);
	mlx->cl.kernel[3] = clCreateKernel(mlx->cl.program, "ship", &mlx->cl.ret);
	mlx->cl.kernel[4] = clCreateKernel(mlx->cl.program, "halley",\
	&mlx->cl.ret);
	mlx->cl.kernel[5] = clCreateKernel(mlx->cl.program, "h1", &mlx->cl.ret);
	mlx->cl.kernel[6] = clCreateKernel(mlx->cl.program, "h2", &mlx->cl.ret);
	mlx->cl.kernel[7] = clCreateKernel(mlx->cl.program, "h3", &mlx->cl.ret);
	mlx->cl.global_item_size = mlx->n;
	mlx->cl.local_item_size = 64;
}

int		ft_opencl_init(t_mlx *mlx)
{
	int i;

	ft_opencl_init_path1(mlx);
	ft_read_cl_program(mlx);
	ft_cl_buffers_eq(mlx);
	ft_cl_kernels_create(mlx);
	i = -1;
	while (++i < 8)
	{
		mlx->cl.ret = clSetKernelArg(mlx->cl.kernel[i], 0, sizeof(cl_mem),\
		(void *)&mlx->cl.re_mem_obj);
		mlx->cl.ret = clSetKernelArg(mlx->cl.kernel[i], 1, sizeof(cl_mem),\
		(void *)&mlx->cl.im_mem_obj);
		mlx->cl.ret = clSetKernelArg(mlx->cl.kernel[i], 2, sizeof(cl_mem),\
		(void *)&mlx->cl.color_mem_obj);
		mlx->cl.ret = clSetKernelArg(mlx->cl.kernel[i], 3, sizeof(cl_mem),\
		(void *)&mlx->cl.control_mem_obj);
	}
	if (mlx->cl.ret)
	{
		ft_putendl("Error");
		exit(1);
	}
	return (0);
}
