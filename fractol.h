/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:21:44 by majosue           #+#    #+#             */
/*   Updated: 2020/03/07 10:01:10 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <OpenCL/opencl.h>

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h> //for testing

# define WIN_WIDTH 600
# define WIN_HEIGHT 400
# define MAX_ITERATIONS 150
# define START_COLOUR 0x854500
# define END_COLOUR 0xdbaa74


typedef union u_colour
{
	int composite;
	unsigned char color[4];
} t_colour;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_point {
	int	color;
	double re;
	double im;
} t_point;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	double		scale;
	double		mouse_x;
	double		mouse_y;
	double		mouse_scale;
	double		mouse_shift_x;
	double		mouse_shift_y;
	int			color_mod;
	int 		n;
	int			mouse_b;
	t_point		*pnt;
	t_point		con;
	t_img		img;
}				t_mlx;


int			ft_get_color(t_mlx *mlx, int current);
//char **ft_readpnt(int fd, int *width, int *height);
//int  ft_draw_line(t_mlx *mlx, t_point p1, t_point p2);

#endif