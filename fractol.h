/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:21:44 by majosue           #+#    #+#             */
/*   Updated: 2020/03/13 16:48:16 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <OpenCL/opencl.h>
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "fractol_opencl.h"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define START_COLOUR 0x0
# define END_COLOUR 0xff0000

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_opencl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				re_mem_obj;
	cl_mem				im_mem_obj;
	cl_mem				color_mem_obj;
	cl_mem				control_mem_obj;
	cl_program			program;
	cl_kernel			kernel[8];
	size_t				global_item_size;
	size_t				local_item_size;
}				t_opencl;

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
	int			n;
	int			mouse_b;
	int			keyboard_b;
	t_control	control;
	double		*re;
	double		*im;
	int			start_fractol;
	int			selected_fractol;
	int			color_step;
	int			color_step2;
	t_opencl	cl;
	t_img		img;
}				t_mlx;

int				ft_get_color(t_mlx *mlx, int current);
int				ft_opencl_init(t_mlx *mlx);
int				ft_mouse_move(int x, int y, t_mlx *mlx);
int				ft_mouse_press(int button, int x, int y, t_mlx *mlx);
int				ft_mouse_release(int button, int x, int y, t_mlx *mlx);
int				ft_keypress(int keycode, t_mlx *mlx);
int				ft_keyrelease(int keycode, t_mlx *mlx);
void			ft_calculate_pts(t_mlx *mlx);
int				ft_zoom(int key, t_mlx *mlx);
int				ft_close(t_mlx *mlx);
void			ft_reset_to_init(t_mlx *mlx);
void			ft_set_start_color(t_mlx *mlx, int keycode);
void			ft_array_init(t_mlx *mlx);
int				ft_loop_hook(t_mlx *mlx);
int				ft_mlx_init(t_mlx *mlx);

#endif
