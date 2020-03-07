/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:20:29 by majosue           #+#    #+#             */
/*   Updated: 2020/03/07 10:58:40 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int ft_close(void *param)
{
	(void)param;
	exit(0);
}

int ft_win_to_log(t_mlx *mlx, int i)
{
	int x;
	int y;

	x = i % WIN_WIDTH;
	y = i / WIN_WIDTH;
	mlx->pnt[i].re = x * 4.0 / WIN_WIDTH - (5.0 / WIN_WIDTH) * WIN_WIDTH / 2;
	mlx->pnt[i].im = y * 4.0 / WIN_WIDTH - (4.0 / WIN_WIDTH) * WIN_HEIGHT / 2;
	mlx->pnt[i].color = 0;
	return (1);
}

void ft_array_init(t_mlx *mlx)
{
	int n;
	int i;

	n = WIN_HEIGHT * WIN_WIDTH;
	i = -1;
	while (++i < n)
	{
		ft_win_to_log(mlx, i);
	}
	mlx->n = n;
}

void ft_mand(double re, double im, t_mlx *mlx, int i)
{
	mlx->pnt[i].re = re;
	mlx->pnt[i].im = im;
}

/* int ft_get_colour(t_mlx *mlx, int iter)
{
	t_colour c;
	c.c[0] = iter * 10;
	c.c[1] = iter * 50;
	c.c[2] = iter * 110;
	return (c.colour);
}
 */
int ft_calculate_pts(t_mlx *mlx)
{
	{
		int m;
		int i;
		int iteration;

		m = WIN_WIDTH * WIN_HEIGHT;
		t_point c;
				
		iteration = 0;
		i = -1;
		while (++i < m)
		{
			c = mlx->pnt[i];
			while (pow(mlx->pnt[i].re, 2.0) + pow(mlx->pnt[i].im, 2.0) <= 4 && iteration < MAX_ITERATIONS)
			{
				ft_mand(pow(mlx->pnt[i].re, 2.0) - pow(mlx->pnt[i].im, 2.0) + mlx->con.re, 2.0 * mlx->pnt[i].re * mlx->pnt[i].im + mlx->con.im, mlx, i);
				iteration++;
			}
			mlx->pnt[i] = c;
			//if (iteration == MAX_ITERATIONS)
			//	mlx->img.data[i] = 0;
		//	else
				mlx->img.data[i] = ft_get_color(mlx, iteration);
			iteration = 0;
		}
		return (1);
	}
}


int ft_zoom(int key, t_mlx *mlx)
{
	int i;
	double dx;
	double dy;

	i = -1;
	if (key == 5)
		mlx->scale = 1.1;
	if (key == 4)
		mlx->scale = 0.9;
	dx = mlx->mouse_x - mlx->mouse_x * mlx->scale;
	dy = mlx->mouse_y - mlx->mouse_y * mlx->scale;
	while (++i < mlx->n)
	{
		mlx->pnt[i].re = mlx->pnt[i].re * mlx->scale + dx;
		mlx->pnt[i].im = mlx->pnt[i].im * mlx->scale + dy;
	}
	mlx->mouse_shift_x = mlx->mouse_shift_x * mlx->scale - dx;
	mlx->mouse_shift_y = mlx->mouse_shift_y * mlx->scale - dy;
	mlx->mouse_scale = mlx->mouse_scale * mlx->scale;
	ft_calculate_pts(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (1);
}

int		ft_mouse_move(int x, int y, t_mlx *mlx)
{
	if (mlx->mouse_b == 3)
		{
			mlx->mouse_x = x * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_x - ((5.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
			mlx->mouse_y = y * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_y - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_HEIGHT / 2;	
		}
	if (mlx->mouse_b == 2)
		{
			mlx->con.re = x * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_x - ((5.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
			mlx->con.im = y * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_y - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_HEIGHT / 2;	
			ft_calculate_pts(mlx);
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
		}	
	//	ft_zoom(0, mlx);
	//	ft_move(0, mlx, x, y);
	return (1);
}


int ft_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse_x = x * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_x - ((5.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
	mlx->mouse_y = y * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_y - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_HEIGHT / 2;
	if (button == 4 || button == 5)
		ft_zoom(button, mlx);
	if ((button == 1 || button == 2 || button == 3) && y > 0)
		mlx->mouse_b = button;
	return (1);
}

int ft_mouse_release(int button, int x, int y, t_mlx *mlx)
{
	double xm;
	double ym;
	double delta_x;
	double delta_y;
	int i;

	i = -1;
	if (button == 1)
		{
		
	xm = x * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_x - ((5.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
	ym = y * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_y - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_HEIGHT / 2;
	delta_x = xm - mlx->mouse_x;
	delta_y = ym - mlx->mouse_y;
	mlx->mouse_shift_x += delta_x;
	mlx->mouse_shift_y += delta_y;
	mlx->mouse_b = 0;
	while (++i < mlx->n)
	{
		mlx->pnt[i].re = mlx->pnt[i].re - delta_x;
		mlx->pnt[i].im = mlx->pnt[i].im - delta_y;
	}
	ft_calculate_pts(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
		}
	mlx->mouse_b = 0;
	return (0);
}

int ft_mlx_init(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fractol");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &(mlx->img.bpp), &(mlx->img.size_l), &(mlx->img.endian));
	return (0);
}
int ft_loop_hook(t_mlx *mlx)
{
	if (mlx->mouse_b == 3)
	{
		ft_zoom(0, mlx);
	}
return (0);
}

void ft_touch_opencl(void)
{
	cl_platform_id platform_id;
	cl_uint ret_num_platforms;
	cl_device_id device_id;
	cl_uint ret_num_devices;
	cl_context context;
	cl_command_queue command_queue;
	int ret;
	
	
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	//printf("platform_id - %d, ret_num_platforms - %d\n", platform_id, ret_num_platforms);
}


int main(int argc, char **argv)
{
	int fd;
	int i;
	t_point *pnt;
	t_mlx mlx;

	if (argc != 2)
	{
		ft_putendl("usage: ./fractol ");
		return (0);
	}
	ft_touch_opencl();
	mlx.pnt = (t_point *)malloc(sizeof(t_point) * WIN_HEIGHT * WIN_WIDTH);
	mlx.scale = 1;
	mlx.mouse_scale = 1;
	mlx.mouse_x = 0;
	mlx.mouse_y = 0;
	mlx.mouse_shift_x = 0;
	mlx.mouse_shift_y = 0;
	mlx.con.re = -0.70176;
	mlx.con.im = -0.3842;
	mlx.mouse_b = 0;
	ft_mlx_init(&mlx);
	ft_array_init(&mlx);
	ft_calculate_pts(&mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win, 17, 1l << 17, &ft_close, 0);
	mlx_hook(mlx.win, 4, 1L << 2, ft_mouse_press, &mlx);
	mlx_hook(mlx.win, 5, 1L << 3, ft_mouse_release, &mlx);
	mlx_hook(mlx.win, 6, 1L << 6, ft_mouse_move, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, ft_loop_hook, &mlx);
	//	mlx_hook(mlx.win, 2, 1l<<17, &ft_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
}