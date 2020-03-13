/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:20:29 by majosue           #+#    #+#             */
/*   Updated: 2020/03/13 15:56:29 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	ft_check_arg(char *str)
{
	char	*valid[8];
	int		i;

	if (!(str = ft_strtrim(str)))
	{
		ft_putendl("Error");
		exit(1);
	}
	i = -1;
	valid[0] = "mandelbrot";
	valid[1] = "julia";
	valid[2] = "newton";
	valid[3] = "ship";
	valid[4] = "halley";
	valid[5] = "h1";
	valid[6] = "h2";
	valid[7] = "h3";
	while (++i < 8 && (ft_strequ(str, valid[i]) == 0))
	{
	}
	free(str);
	return (i);
}

int	main(int argc, char **argv)
{
	t_mlx mlx;

	if (argc != 2 || (mlx.start_fractol = ft_check_arg(argv[1])) > 7)
	{
		ft_putendl("usage: ./fractol mandelbrot | julia | \
		newton | ship | halley | h1 | h2 | h3");
		return (0);
	}
	mlx.selected_fractol = mlx.start_fractol;
	ft_mlx_init(&mlx);
	ft_array_init(&mlx);
	ft_opencl_init(&mlx);
	ft_calculate_pts(&mlx);
	mlx_hook(mlx.win, 17, 1l << 17, &ft_close, 0);
	mlx_hook(mlx.win, 4, 1L << 2, ft_mouse_press, &mlx);
	mlx_hook(mlx.win, 5, 1L << 3, ft_mouse_release, &mlx);
	mlx_hook(mlx.win, 6, 1L << 6, ft_mouse_move, &mlx);
	mlx_hook(mlx.win, 2, 1L << 6, ft_keypress, &mlx);
	mlx_hook(mlx.win, 3, 1L << 6, ft_keyrelease, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, ft_loop_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
