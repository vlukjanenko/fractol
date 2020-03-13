/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 14:53:15 by majosue           #+#    #+#             */
/*   Updated: 2020/03/13 15:36:02 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_mouse_move(int x, int y, t_mlx *mlx)
{
	if (mlx->mouse_b == 3)
	{
		mlx->mouse_x = x * (4.0) / WIN_WIDTH * mlx->mouse_scale -
mlx->mouse_shift_x - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
		mlx->mouse_y = y * (4.0) / WIN_WIDTH * mlx->mouse_scale -
mlx->mouse_shift_y - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_HEIGHT / 2;
	}
	if (mlx->keyboard_b == 257)
	{
		mlx->control.c.re = x * (4.0) / WIN_WIDTH * mlx->mouse_scale -
mlx->mouse_shift_x - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
		mlx->control.c.im = y * (4.0) / WIN_WIDTH * mlx->mouse_scale -
mlx->mouse_shift_y - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_HEIGHT / 2;
		ft_calculate_pts(mlx);
	}
	return (0);
}

int	ft_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse_x = x * (4.0) / WIN_WIDTH * mlx->mouse_scale -
mlx->mouse_shift_x - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
	mlx->mouse_y = y * (4.0) / WIN_WIDTH * mlx->mouse_scale -
mlx->mouse_shift_y - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_HEIGHT / 2;
	if (button == 4 || button == 5)
		ft_zoom(button, mlx);
	if ((button == 1 || button == 2 || button == 3) && y > 0)
		mlx->mouse_b = button;
	return (0);
}

int	ft_mouse_release(int button, int x, int y, t_mlx *mlx)
{
	double	xm;
	double	ym;
	int		i;

	i = -1;
	if (button == 1)
	{
		xm = x * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_x -
((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
		ym = y * (4.0) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_y -
((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_HEIGHT / 2;
		mlx->mouse_shift_x += (xm - mlx->mouse_x);
		mlx->mouse_shift_y += (ym - mlx->mouse_y);
		mlx->mouse_b = 0;
		while (++i < mlx->n)
		{
			mlx->re[i] = mlx->re[i] - (xm - mlx->mouse_x);
			mlx->im[i] = mlx->im[i] - (ym - mlx->mouse_y);
		}
		ft_calculate_pts(mlx);
	}
	mlx->mouse_b = 0;
	return (0);
}

int	ft_keypress(int keycode, t_mlx *mlx)
{
	if (keycode == 67)
	{
		mlx->control.color_mod = mlx->control.color_mod ? 0 : 1;
		ft_calculate_pts(mlx);
	}
	if (keycode == 78 || keycode == 69)
		ft_set_start_color(mlx, keycode);
	if (keycode == 53)
		ft_close(mlx);
	if (keycode == 48)
		mlx->selected_fractol = (mlx->selected_fractol < 7) ?\
		mlx->selected_fractol + 1 : 0;
	if (keycode == 257)
		mlx->keyboard_b = 257;
	if (keycode == 15 || keycode == 48)
	{
		ft_reset_to_init(mlx);
		ft_array_init(mlx);
		ft_calculate_pts(mlx);
	}
	return (0);
}

int	ft_keyrelease(int keycode, t_mlx *mlx)
{
	(void)keycode;
	mlx->keyboard_b = 0;
	return (0);
}
