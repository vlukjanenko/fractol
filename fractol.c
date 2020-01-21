/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:20:29 by majosue           #+#    #+#             */
/*   Updated: 2020/01/21 13:52:51 by majosue          ###   ########.fr       */
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
	mlx->pnt[i].re = (x / ((1.0 / 4) * WIN_WIDTH) - 3); 
	mlx->pnt[i].im = (y / ((-1.0 / 3) *  WIN_HEIGHT) + 1.5);
return (1);
}

void ft_array_init(t_mlx *mlx)
{
	int n;
	int i;

	n = WIN_HEIGHT * WIN_WIDTH;
	i = -1;
	while(++i < n)
	{
		ft_win_to_log(mlx, i);
	}
}
void ft_mand(double re, double im, t_mlx *mlx, int i)
{
	mlx->pnt[i].re = re;
	mlx->pnt[i].im = im;
}
int ft_get_colour(t_mlx *mlx, int iter)
{
	mlx->col.c[0] = iter * 5;
	mlx->col.c[1] = iter * 7;
	mlx->col.c[2] = iter * 2;
	return (mlx->col.colour);
}

int ft_zoom(int key, t_mlx *mlx)
{
	mlx->scale = (key == 5 || key == 78) ? mlx->scale * 1.2 : mlx->scale / 1.2;
	//mlx->scale = (key == 5 || key == 78) ? 1.1 : 0.9;
	return (1); 
}
int		ft_mouse_move(int x, int y, t_mlx *mlx)
{
	/* mlx->mouse_x = ((x / ((1.0 / 4) * WIN_WIDTH) - 3) ) * mlx->scale + mlx->center_x;
	mlx->mouse_y = ((y / ((-1.0 / 3) *  WIN_HEIGHT) + 1.5) ) * mlx->scale + mlx->center_y; */
	mlx->mouse_x  = (x / ((1.0 / 4) * WIN_WIDTH) - 3) * mlx->scale;
	mlx->mouse_y  = (y / ((-1.0 / 3) *  WIN_HEIGHT) + 1.5) * mlx->scale;
	printf("zoom = %f, mouse recalc = %f, %f\n",mlx->scale, mlx->mouse_x, mlx->mouse_y);
	return (0);
}
void ft_draw_cord(t_mlx *mlx)
{
	int i;
	int n;

	i = -1;
	n =  WIN_WIDTH * WIN_HEIGHT;

	while (++i < n)
	{
		if (!(mlx->pnt[i].re - mlx->mouse_x) || !(mlx->pnt[i].im - mlx->mouse_y))
		{
			mlx->img.data[i] = 0xFFFFFF;
		}
	}

}
int ft_draw(t_mlx *mlx)
{
	int m;
	int i;
	int iteration;
	double dx;
	double dy;
	t_point c;
	ft_array_init(mlx);		
	iteration = 0;
	mlx->col.colour = 0;
	i = -1;
	mlx_clear_window((*mlx).mlx_ptr, (*mlx).win);
	m = WIN_WIDTH * WIN_HEIGHT;
	while (++i < m)
		(*mlx).img.data[i] = 0xffffff;	
	i = -1;
	while (++i < m)
	{
		
		mlx->pnt[i].re *= mlx->scale; // переставили в ноль и смасштабировали
		mlx->pnt[i].im *= mlx->scale; //
		dx = mlx->mouse_x - mlx->mouse_x * mlx->scale;
		dy = mlx->mouse_y - mlx->mouse_y * mlx->scale;
		mlx->pnt[i].re = mlx->pnt[i].re + dx;  // вернули обратно соответственно все координаты окна уже другие 
		mlx->pnt[i].im = mlx->pnt[i].im + dy;  //
	/*
		когда берем следующи цент масштабирования нужно пересчитывать точку как если бы мы изначально тыкались в нее?
	*/ 
	//	printf("center object = %f, %f\n", mlx->center_x, mlx->center_y);
	
		c = mlx->pnt[i];
		while (pow(mlx->pnt[i].re, 2.0) + pow(mlx->pnt[i].im, 2.0) <= 4 && iteration < MAX_ITERATIONS)
        {
			ft_mand(pow(mlx->pnt[i].re, 2.0) - pow(mlx->pnt[i].im, 2.0) + c.re, 2.0 * mlx->pnt[i].re * mlx->pnt[i].im + c.im, mlx, i);
			iteration++;
        }
		mlx->pnt[i] = c;
		//ft_log_to_win(mlx); // вот тут должны сместить относительно мышки, смасштабировать и вернуть обратно
		if (iteration == MAX_ITERATIONS)	
			mlx->img.data[i] = 0;
		else 
			mlx->img.data[i] = ft_get_colour(mlx, iteration);
		iteration = 0;
	}
	//ft_log_to_win(mlx);
	ft_draw_cord(mlx);
	mlx_put_image_to_window((*mlx).mlx_ptr, (*mlx).win, (*mlx).img.img_ptr, 0, 0);
	return (1);
}

int ft_keypress(int keycode, void *mlx)
{
	if(keycode == 53)
		ft_close(0);
	if (keycode == 78 || keycode == 69)
		{
			ft_zoom(keycode, mlx);
			ft_draw(mlx);
		}
	return (1);
}

int		ft_mouse_press(int button, int x, int y, t_mlx *mlx) // вот тут надо как то компенсировать
{


mlx->center_x = mlx->mouse_x * mlx->scale - mlx->mouse_x;
mlx->center_y = mlx->mouse_y * mlx->scale - mlx->mouse_y;
mlx->mouse_xp  = mlx->mouse_x;
mlx->mouse_yp  = mlx->mouse_y;
mlx->mouse_x  = (x / ((1.0 / 4) * WIN_WIDTH) - 3);
mlx->mouse_y  = (y / ((-1.0 / 3) *  WIN_HEIGHT) + 1.5);

	if (button == 4 || button == 5)
		ft_zoom(button, mlx);
		ft_draw(mlx);
	return (1);
}

int main(int argc, char **argv)
{
	int fd;
	int i;
	t_point *pnt;	
	t_mlx	mlx;

	if (argc != 2)
	{
		ft_putendl("usage: ./fractol ");
		return (0);
	}
	mlx.pnt = (t_point *)malloc(sizeof(t_point) * WIN_HEIGHT * WIN_WIDTH);
	mlx.scale = 1;
	mlx.mouse_x = 0;
	mlx.mouse_y = 0;
	mlx.mouse_xp = 0;
	mlx.mouse_yp = 0;
	ft_array_init(&mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, argv[1]);
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	ft_draw(&mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win, 17, 1l<<17, &ft_close, 0);
	mlx_hook(mlx.win, 4, 1L << 2, ft_mouse_press, &mlx);
	mlx_hook(mlx.win, 6, 1L << 6, ft_mouse_move, &mlx);
	mlx_hook(mlx.win, 2, 1l<<17, &ft_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
}