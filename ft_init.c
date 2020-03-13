/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:09:00 by majosue           #+#    #+#             */
/*   Updated: 2020/03/13 15:15:13 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_close(t_mlx *mlx)
{
	(void)mlx;
	exit(0);
}

void	ft_array_init(t_mlx *mlx)
{
	int i;
	int x;
	int y;

	mlx->n = WIN_HEIGHT * WIN_WIDTH;
	i = -1;
	while (++i < mlx->n)
	{
		x = i % WIN_WIDTH;
		y = i / WIN_WIDTH;
		mlx->re[i] = x * 4.0 / WIN_WIDTH * mlx->mouse_scale -
mlx->mouse_shift_x - (4.0 / WIN_WIDTH) * WIN_WIDTH / 2;
		mlx->im[i] = y * 4.0 / WIN_WIDTH * mlx->mouse_scale -
mlx->mouse_shift_y - (4.0 / WIN_WIDTH) * WIN_HEIGHT / 2;
	}
}

void	ft_reset_to_init(t_mlx *mlx)
{
	mlx->scale = 1;
	mlx->mouse_scale = 1;
	mlx->mouse_x = 0;
	mlx->mouse_y = 0;
	mlx->mouse_shift_x = (mlx->selected_fractol == 0) ? 0.4 : 0;
	mlx->mouse_shift_y = 0;
	mlx->control.color_mod = 1;
	mlx->control.c.re = -0.70176;
	mlx->control.c.im = -0.3842;
	mlx->control.start_color = START_COLOUR;
	mlx->control.end_color = END_COLOUR;
	mlx->control.max_iterations = MAX_ITERATIONS;
	mlx->color_step = 0;
	mlx->mouse_b = 0;
	mlx->keyboard_b = 0;
}

int		ft_mlx_init(t_mlx *mlx)
{
	if (!(mlx->mlx_ptr = mlx_init()) ||
!(mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fractol")) ||
!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT)) ||
!(mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &(mlx->img.bpp),
&(mlx->img.size_l), &(mlx->img.endian))) ||
!(mlx->re = (double *)malloc(sizeof(double) * WIN_HEIGHT * WIN_WIDTH)) ||
!(mlx->im = (double *)malloc(sizeof(double) * WIN_HEIGHT * WIN_WIDTH)))
	{
		ft_putendl("Error");
		exit(1);
	}
	ft_reset_to_init(mlx);
	return (0);
}

int		ft_loop_hook(t_mlx *mlx)
{
	if (mlx->mouse_b == 3)
	{
		ft_zoom(0, mlx);
	}
	return (0);
}
