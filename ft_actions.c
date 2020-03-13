/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:18:38 by majosue           #+#    #+#             */
/*   Updated: 2020/03/13 15:46:32 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_calculate_pts(t_mlx *mlx)
{
	mlx->cl.ret = clEnqueueWriteBuffer(mlx->cl.command_queue,
mlx->cl.re_mem_obj, CL_TRUE, 0, mlx->n * sizeof(double),
mlx->re, 0, NULL, NULL);
	mlx->cl.ret = clEnqueueWriteBuffer(mlx->cl.command_queue,
mlx->cl.im_mem_obj, CL_TRUE, 0, mlx->n * sizeof(double),
mlx->im, 0, NULL, NULL);
	mlx->cl.ret = clEnqueueWriteBuffer(mlx->cl.command_queue,
mlx->cl.control_mem_obj, CL_TRUE, 0, sizeof(t_control),
&mlx->control, 0, NULL, NULL);
	mlx->cl.ret = clEnqueueNDRangeKernel(mlx->cl.command_queue,
mlx->cl.kernel[mlx->selected_fractol], 1, NULL,
&mlx->cl.global_item_size, &mlx->cl.local_item_size, 0, NULL, NULL);
	mlx->cl.ret = clEnqueueReadBuffer(mlx->cl.command_queue,
mlx->cl.color_mem_obj, CL_TRUE, 0, mlx->n * sizeof(int),
mlx->img.data, 0, NULL, NULL);
	if (mlx->cl.ret)
	{
		ft_putendl("Error");
		exit(1);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win,
mlx->img.img_ptr, 0, 0);
	mlx_string_put(mlx->mlx_ptr, mlx->win, 10, 10, 0xFFFFFF, "r - reset,\
TAB - switch, shift (change c for julia), \"+\", \"-\"\
- change color in mode1 \"*\" - change mode");
}

int		ft_zoom(int key, t_mlx *mlx)
{
	int		i;
	double	dx;
	double	dy;

	i = -1;
	if (key == 5)
		mlx->scale = 1.1;
	if (key == 4)
		mlx->scale = 0.9;
	dx = mlx->mouse_x - mlx->mouse_x * mlx->scale;
	dy = mlx->mouse_y - mlx->mouse_y * mlx->scale;
	while (++i < mlx->n)
	{
		mlx->re[i] = mlx->re[i] * mlx->scale + dx;
		mlx->im[i] = mlx->im[i] * mlx->scale + dy;
	}
	mlx->mouse_shift_x = mlx->mouse_shift_x * mlx->scale - dx;
	mlx->mouse_shift_y = mlx->mouse_shift_y * mlx->scale - dy;
	mlx->mouse_scale = mlx->mouse_scale * mlx->scale;
	ft_calculate_pts(mlx);
	return (0);
}

void	ft_set_start_color(t_mlx *mlx, int keycode)
{
	int			i;
	t_colour	tmp;

	i = 0;
	tmp.composite = END_COLOUR;
	if (keycode == 69 && mlx->color_step < 1530)
		mlx->color_step += 153;
	if (keycode == 78 && mlx->color_step > 0)
		mlx->color_step -= 153;
	while (tmp.color[0] < 255 && ++i < mlx->color_step + 1)
		tmp.color[0]++;
	while (tmp.color[3] > 0 && ++i < mlx->color_step + 2)
		tmp.color[3]--;
	while (tmp.color[1] < 255 && ++i < mlx->color_step + 3)
		tmp.color[1]++;
	while (tmp.color[0] > 0 && ++i < mlx->color_step + 4)
		tmp.color[0]--;
	while (tmp.color[3] < 255 && ++i < mlx->color_step + 5)
		tmp.color[3]++;
	while (tmp.color[1] > 0 && ++i < mlx->color_step + 6)
		tmp.color[1]--;
	mlx->control.end_color = tmp.composite;
	ft_calculate_pts(mlx);
}
