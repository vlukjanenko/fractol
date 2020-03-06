/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:21:44 by majosue           #+#    #+#             */
/*   Updated: 2020/03/06 08:59:12 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h> //for testing

# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define MAX_ITERATIONS 150

typedef union u_colour
{
	int colour;
	unsigned char c[4];
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
	int			stcol;
	int			endcol;
	double		scale;
	double		mouse_scale;
	double		scale_prev;
	double 		center_x;
	double		center_y;
	double		mouse_xp;
	double		mouse_yp;
	double		mouse_x;
	double		mouse_y;
	double		mouse_shift_x;
	double		mouse_shift_y;
	int 		n;
	int			 mouse_b;
	t_colour	col;
	t_point		*pnt;
	t_img		img;
}				t_mlx;



//char **ft_readpnt(int fd, int *width, int *height);
//int  ft_draw_line(t_mlx *mlx, t_point p1, t_point p2);

#endif