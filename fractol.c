/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:20:29 by majosue           #+#    #+#             */
/*   Updated: 2020/03/06 14:20:15 by majosue          ###   ########.fr       */
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
	mlx->pnt[i].re = x * (4.0 * mlx->scale) / WIN_WIDTH;/// - ((4.0 * mlx->scale) / WIN_WIDTH) * WIN_WIDTH / 2; 
	mlx->pnt[i].im = y * (4.0 * mlx->scale) / WIN_HEIGHT;// - ((4.0 * mlx->scale)/ WIN_WIDTH) * WIN_WIDTH / 2;
//		printf("re = %f, im = %f\n", mlx->pnt[i].re, mlx->pnt[i].re);
	mlx->pnt[i].color = 0;
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
	mlx->pnt[n].re = 0;
	mlx->pnt[n].im = 0;
	mlx->n = n;
}
void ft_mand(double re, double im, t_mlx *mlx, int i)
{
	mlx->pnt[i].re = re;
	mlx->pnt[i].im = im;
}
int ft_get_colour(t_mlx *mlx, int iter)
{
	t_colour c;
	c.c[0] = iter * 10;
	c.c[1] = iter * 10;
	c.c[2] = iter * 10;
	return (c.colour);
} 

/* int		ft_mouse_move(int x, int y, t_mlx *mlx)
{
	printf("zoom = %f, mouse recalc = %f, %f\n",mlx->scale, mlx->mouse_x, mlx->mouse_y);
	return (0);
} */
/* void ft_draw_cord(t_mlx *mlx)
{
	int i;
	int n;

	i = -1;
	n =  WIN_WIDTH * WIN_HEIGHT;

	while (++i < n)
	{
		if (mlx->pnt[i].re == mlx->center_x || mlx->pnt[i].im == mlx->center_y)
		{
			mlx->img.data[i] = 0xFFFFFF;
		}
	}

} */
/* int ft_draw(t_mlx *mlx)
{
	int m;
	int i;
	int iteration;
	double dx;
	double dy;
	
	t_point c;
	
	//ft_array_init(mlx);		
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
		mlx->pnt[i].re *= mlx->scale; // смасштабировали
		mlx->pnt[i].im *= mlx->scale; //
		dx = mlx->mouse_x - mlx->mouse_x * mlx->scale;
		dy = mlx->mouse_y - mlx->mouse_y * mlx->scale;
		mlx->pnt[i].re = mlx->pnt[i].re + dx;  // вернули обратно соответственно все координаты окна уже другие 
		mlx->pnt[i].im = mlx->pnt[i].im + dy;  //
		

		c = mlx->pnt[i];
		while (pow(mlx->pnt[i].re, 2.0) + pow(mlx->pnt[i].im, 2.0) <= 4 && iteration < MAX_ITERATIONS)
        {
			ft_mand(pow(mlx->pnt[i].re, 2.0) - pow(mlx->pnt[i].im, 2.0) + c.re, 2.0 * mlx->pnt[i].re * mlx->pnt[i].im + c.im, mlx, i);
			iteration++;
        }
		mlx->pnt[i] = c;
		if (iteration == MAX_ITERATIONS)	
			mlx->img.data[i] = 0;
		else 
			mlx->img.data[i] = ft_get_colour(mlx, iteration);
		iteration = 0;
	}
	mlx_put_image_to_window((*mlx).mlx_ptr, (*mlx).win, (*mlx).img.img_ptr, 0, 0);
	return (1);
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
		/* mlx->pnt[i].re *= mlx->scale; // смасштабировали
		mlx->pnt[i].im *= mlx->scale; //
		dx = mlx->mouse_x - mlx->mouse_x * mlx->scale;
		dy = mlx->mouse_y - mlx->mouse_y * mlx->scale;
		mlx->pnt[i].re = mlx->pnt[i].re + dx;  // вернули обратно соответственно все координаты окна уже другие 
		mlx->pnt[i].im = mlx->pnt[i].im + dy;  //
		 */

		c = mlx->pnt[i]; //запомнили точку
		while (pow(mlx->pnt[i].re, 2.0) + pow(mlx->pnt[i].im, 2.0) <= 4 && iteration < MAX_ITERATIONS)
        {
			ft_mand(pow(mlx->pnt[i].re, 2.0) - pow(mlx->pnt[i].im, 2.0) + c.re, 2.0 * mlx->pnt[i].re * mlx->pnt[i].im + c.im, mlx, i);
			iteration++;
        }
		mlx->pnt[i] = c; //вернули взад
		if (iteration == MAX_ITERATIONS)	
			mlx->img.data[i] = 0;
		else 
			{
				mlx->img.data[i] = ft_get_colour(mlx, iteration);
				
			}
			//printf("color = %d\n", mlx->img.data[i]);
		iteration = 0;
	}
	return (1);
}

}


/* 
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
} */
int ft_zoom(int key, t_mlx *mlx)
{
	int i;
	double dx;
	double dy;


	i = -1;
	
	mlx->scale = (key == 5 || key == 78) ? 1.1 : 0.9;
	
	
	dx = mlx->mouse_x - mlx->mouse_x * mlx->scale;
	dy = mlx->mouse_y - mlx->mouse_y * mlx->scale; 
	
	while (++i < mlx->n)
	{
	//mlx->pnt[i].re *= mlx->scale; //(mlx->pnt[i].re - mlx->mouse_x) * mlx->scale + mlx->mouse_x; 
	//mlx->pnt[i].im *= mlx->scale; //(mlx->pnt[i].im - mlx->mouse_y) * mlx->scale + mlx->mouse_y; 
	
		mlx->pnt[i].re = mlx->pnt[i].re * mlx->scale + dx;  // вернули обратно соответственно все координаты окна уже другие 
		mlx->pnt[i].im = mlx->pnt[i].im * mlx->scale + dy;  //
		

		//mlx->pnt[i].re = mlx->pnt[i].re + dx;  // вернули обратно соответственно все координаты окна уже другие 
		//mlx->pnt[i].im = mlx->pnt[i].im + dy;  //		
	}
	
	mlx->mouse_shift_x = mlx->mouse_shift_x * mlx->scale - dx;
	mlx->mouse_shift_y = mlx->mouse_shift_y * mlx->scale - dy;
	mlx->mouse_scale = mlx->mouse_scale * mlx->scale;
	printf("scale = %f", mlx->scale);
	ft_calculate_pts(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);

	return (1); 
}
int		ft_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse_xp = mlx->mouse_x;
	mlx->mouse_yp = mlx->mouse_y;
	mlx->mouse_x = x * (4.0 ) / WIN_WIDTH * mlx->mouse_scale - mlx->mouse_shift_x;// - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
	mlx->mouse_y = y * (4.0 ) / WIN_WIDTH *  mlx->mouse_scale - mlx->mouse_shift_y;// - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
	printf("mouse press : %f, %f\n", mlx->mouse_x, mlx->mouse_y);
	if (button == 4 || button == 5)
		ft_zoom(button, mlx);
	if ((button == 1 || button == 2) && y > 0)
		mlx->mouse_b = button;
	return (1);
}

int		ft_mouse_release(int button, int x, int y, t_mlx *mlx) //вот тут перемещение отрабатываем на отпускании кнопки
{
	double xm;
	double ym;
	int i;
	//printf("заходит по колесу"); //нифига не заходит
	i = -1;
	xm = x * (4.0) / WIN_WIDTH *  mlx->mouse_scale - mlx->mouse_shift_x;// - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2; 
	ym = y * (4.0) / WIN_WIDTH *  mlx->mouse_scale - mlx->mouse_shift_y;// - ((4.0 * mlx->mouse_scale) / WIN_WIDTH) * WIN_WIDTH / 2;
	mlx->pnt[mlx->n].re = xm - mlx->mouse_x;  // это при сдвиге
	mlx->pnt[mlx->n].im = ym - mlx->mouse_y;  // а при масштабировании нужно тоже прописывать
	mlx->mouse_shift_x += mlx->pnt[mlx->n].re;
	mlx->mouse_shift_y += mlx->pnt[mlx->n].im;
	mlx->mouse_b = 0;
	while (++i < mlx->n)
	{
		mlx->pnt[i].re = mlx->pnt[i].re - mlx->pnt[mlx->n].re;
		mlx->pnt[i].im = mlx->pnt[i].im - mlx->pnt[mlx->n].im;
	}
	ft_calculate_pts(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (1);
}

int ft_mlx_init(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fractol");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &(mlx->img.bpp), &(mlx->img.size_l), &(mlx->img.endian));
return (0);
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
	mlx.pnt = (t_point *)malloc(sizeof(t_point) * (WIN_HEIGHT * WIN_WIDTH + 1)); // на однушку больше чтобы хранить центр
	mlx.scale = 1;
	mlx.mouse_scale = 1;
	mlx.mouse_x = 0;
	mlx.mouse_y = 0;
	mlx.mouse_shift_x = 0;
	mlx.mouse_shift_y = 0;
	mlx.mouse_xp = 0;
	mlx.mouse_yp = 0;
	ft_mlx_init(&mlx);
	ft_array_init(&mlx);
	ft_calculate_pts(&mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	/* mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, argv[1]);
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	ft_draw(&mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0); */
	mlx_hook(mlx.win, 17, 1l<<17, &ft_close, 0);
	mlx_hook(mlx.win, 4, 1L << 2, ft_mouse_press, &mlx);
	mlx_hook(mlx.win, 5, 1L << 3, ft_mouse_release, &mlx);
//	mlx_hook(mlx.win, 6, 1L << 6, ft_mouse_move, &mlx);
//	mlx_hook(mlx.win, 2, 1l<<17, &ft_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
}