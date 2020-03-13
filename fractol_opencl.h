/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_opencl.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 10:57:19 by majosue           #+#    #+#             */
/*   Updated: 2020/03/13 16:05:10 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_OPENCL_H
# define FRACTOL_OPENCL_H
# define MAX_SOURCE_SIZE 0x100000

typedef union	u_colour
{
	int				composite;
	unsigned char	color[4];
}				t_colour;

typedef struct	s_complex
{
	double re;
	double im;
}				t_complex;

typedef struct	s_sontrol
{
	t_complex	c;
	int			start_color;
	int			end_color;
	int			max_iterations;
	int			color_mod;
}				t_control;

#endif
