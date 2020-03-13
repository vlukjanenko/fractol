# include "fractol_opencl.h"

double		percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

unsigned char	get_light(unsigned char start, unsigned char end, double pnt)
{
	return ((unsigned char)((1 - pnt) * start + pnt * end));
}

int			ft_set_light(double percentage, int start_color, int end_color)
{
	t_colour start;
	t_colour end;
	t_colour result;

	start.composite = start_color;
	end.composite = end_color;
	result.color[0] = get_light((start.color)[0], (end.color)[0], percentage);
	result.color[1] = get_light((start.color)[1], (end.color)[1], percentage);
	result.color[2] = get_light((start.color)[2], (end.color)[2], percentage);
   	result.color[3] = 0;
    return (result.composite);
}

int			ft_get_color(int current, int start_color, int end_color, int color_mod)
{
	int		color;
	double	p;
	int start;
	int end;
	int max;
	int reverce;
	t_colour c;
	
	if (color_mod == 1)
	{
		c.composite = start_color;
		c.color[0] = 9 * current;
		c.color[1] = 7 * current;
		c.color[2] = 2 * current;
		return (c.composite);
	}
	reverce = 1;
	start = 0;
	max = MAX_ITERATIONS;
	end = (max - start) / 2;
	while (end < max - 1)
	{
		if (current >= start && current < end)
		{
			if (reverce)
				{
					p = percent(start, end, current);
					reverce = 0;
				}
			else
				{
					p = percent(end, start, current);
					reverce = 1;
				}
		color = ft_set_light(p, start_color, end_color);
		return (color);
		}
		start = end;
		end = end + (max - start) / 2;
	
	}
	return (start_color);
}

t_complex c_sub(t_complex z1, t_complex z2)
{
	t_complex z;

	z.re = z1.re - z2.re;
	z.im = z1.im - z2.im;
	return (z);
}

t_complex c_mul(t_complex z1, t_complex z2)
{
	t_complex z;

	z.re = z1.re * z2.re - z1.im * z2.im;
	z.im = z1.re *z2.im + z1.im * z2.re;
	return (z);
}

t_complex c_div(t_complex z1, t_complex z2)
{
	t_complex z;

	z.re = (z1.re * z2.re + z1.im * z2.im) / (pow(z2.re, 2) + pow(z2.im, 2));
	z.im = (-z1.re *z2.im + z1.im * z2.re) / (pow(z2.re, 2) + pow(z2.im, 2));
	return (z);
}

t_complex c_pow(t_complex z1, int power)
{
	t_complex z;
	int i;
	
	i = -1;
	z.re = 1;
	z.im = 0;
	while (++i <  power)
		z = c_mul(z, z1);
	return (z);
}

double c_abs(t_complex z1)
{
	double res;

	res = sqrt(pow(z1.re, 2) + pow(z1.im, 2));
	return (res);
}

__kernel void mandelbrot(__global const double *re, __global const double *im, __global int *color, __global t_control *control) 
{
	int i = get_global_id(0);
	int iteration;
	t_complex z;
	t_complex z1;

	iteration = 0;
	z.im = im[i];
	z.re = re[i];
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && iteration <= control->max_iterations)
	{
		z1.re = pow(z.re, 2.0) - pow(z.im, 2.0) + re[i];
		z1.im = 2.0 * z.re * z.im + im[i];
		z = z1;
		iteration++;
	}
color[i] = ft_get_color(iteration, control->start_color, control->end_color, control->color_mod);
}

__kernel void halley(__global const double *re, __global const double *im, __global int *color, __global t_control *control) 
{
	int i = get_global_id(0);
	int iteration;
	int order;
	double epsilon;
	double magnitude;
	double magnitude1;
	t_complex r;
	t_complex z;
	t_complex z1;
	t_complex z2;
	t_complex z3;
	t_complex z4;
	t_complex z5;
	t_complex z6;
	

	iteration = 0;
	z.im = im[i];
	z.re = re[i];
	order = 12;
	epsilon = 0.001;
	r.re = 1;
	r.im = 0.1;
	while (fabs(magnitude1 - magnitude) > epsilon && iteration <= control->max_iterations)
	{
		z2 = c_pow(z, order - 1);
		z3 = c_mul(z, z2);
		z4.re = z3.re - 1;
		z4.im = z3.im;
		z4 = c_mul(z, z4);
		z5.re = (order + 1) * z3.re - 1;
		z5.im = (order + 1) * z3.im;
		z6.re = order * (order + 1) * z2.re;
		z6.im = order * (order + 1) * z2.im;
		z1.re = z5.re * 2;
		z1.im = z5.im * 2;
		z1 = c_div(c_mul(z4, z6), z1);
		z1 = c_sub(z, c_div(c_mul(r, z4), c_sub(z5, z1)));
		magnitude1 = z1.re;
		magnitude = z.re;
		z = z1;
		iteration++;
	}
color[i] = ft_get_color(iteration, control->start_color, control->end_color, control->color_mod);
}

__kernel void h1(__global const double *re, __global const double *im, __global int *color, __global t_control *control) 
{
	int i = get_global_id(0);
	int iteration;
	int order;
	double epsilon;
	double magnitude;
	double magnitude1;
	t_complex r;
	t_complex z;
	t_complex z1;
	t_complex z2;
	t_complex z3;
	t_complex z4;
	t_complex z5;
	t_complex z6;
	

	iteration = 0;
	z.im = im[i];
	z.re = re[i];
	order = 5;
	epsilon = 0.0001;
	r.re = 0.3;
	r.im = 0.3;
	while (fabs(magnitude1 - magnitude) > epsilon && iteration <= control->max_iterations)
	{
		z2 = c_pow(z, order - 1);
		z3 = c_mul(z, z2);
		z4.re = z3.re - 1;
		z4.im = z3.im;
		z4 = c_mul(z, z4);
		z5.re = (order + 1) * z3.re - 1;
		z5.im = (order + 1) * z3.im;
		z6.re = order * (order + 1) * z2.re;
		z6.im = order * (order + 1) * z2.im;
		z1.re = z5.re * 2;
		z1.im = z5.im * 2;
		z1 = c_div(c_mul(z4, z6), z1);
		z1 = c_sub(z, c_div(c_mul(r, z4), c_sub(z5, z1)));
		magnitude1 = z1.re;
		magnitude = z.re;
		z = z1;
		iteration++;
	}
color[i] = ft_get_color(iteration, control->start_color, control->end_color, control->color_mod);
}

__kernel void h2(__global const double *re, __global const double *im, __global int *color, __global t_control *control) 
{
	int i = get_global_id(0);
	int iteration;
	int order;
	double epsilon;
	double magnitude;
	double magnitude1;
	t_complex r;
	t_complex z;
	t_complex z1;
	t_complex z2;
	t_complex z3;
	t_complex z4;
	t_complex z5;
	t_complex z6;
	

	iteration = 0;
	z.im = im[i];
	z.re = re[i];
	order = -3;
	epsilon = 0.0001;
	r.re = 1;
	r.im = -0.5;
	while (fabs(magnitude1 - magnitude) > epsilon && iteration <= control->max_iterations)
	{
		z2 = c_pow(z, order - 1);
		z3 = c_mul(z, z2);
		z4.re = z3.re - 1;
		z4.im = z3.im;
		z4 = c_mul(z, z4);
		z5.re = (order + 1) * z3.re - 1;
		z5.im = (order + 1) * z3.im;
		z6.re = order * (order + 1) * z2.re;
		z6.im = order * (order + 1) * z2.im;
		z1.re = z5.re * 2;
		z1.im = z5.im * 2;
		z1 = c_div(c_mul(z4, z6), z1);
		z1 = c_sub(z, c_div(c_mul(r, z4), c_sub(z5, z1)));
		magnitude1 = z1.re;
		magnitude = z.re;
		z = z1;
		iteration++;
	}
color[i] = ft_get_color(iteration, control->start_color, control->end_color, control->color_mod);
}

__kernel void h3(__global const double *re, __global const double *im, __global int *color, __global t_control *control) 
{
	int i = get_global_id(0);
	int iteration;
	int order;
	double epsilon;
	double magnitude;
	double magnitude1;
	t_complex r;
	t_complex z;
	t_complex z1;
	t_complex z2;
	t_complex z3;
	t_complex z4;
	t_complex z5;
	t_complex z6;
	

	iteration = 0;
	z.im = im[i];
	z.re = re[i];
	order = 2;
	epsilon = 0.001;
	r.re = 0.3;
	r.im = 0.04;
	while (fabs(magnitude1 - magnitude) > epsilon && iteration <= control->max_iterations)
	{
		z2 = c_pow(z, order - 1);
		z3 = c_mul(z, z2);
		z4.re = z3.re - 1;
		z4.im = z3.im;
		z4 = c_mul(z, z4);
		z5.re = (order + 1) * z3.re - 1;
		z5.im = (order + 1) * z3.im;
		z6.re = order * (order + 1) * z2.re;
		z6.im = order * (order + 1) * z2.im;
		z1.re = z5.re * 2;
		z1.im = z5.im * 2;
		z1 = c_div(c_mul(z4, z6), z1);
		z1 = c_sub(z, c_div(c_mul(r, z4), c_sub(z5, z1)));
		magnitude1 = z1.re;
		magnitude = z.re;
		z = z1;
		iteration++;
	}
color[i] = ft_get_color(iteration, control->start_color, control->end_color, control->color_mod);
}

__kernel void ship(__global const double *re, __global const double *im, __global int *color, __global t_control *control) 
{
	int i = get_global_id(0);
	int iteration;
	t_complex z;
	t_complex z1;
	
	iteration = 0;
	z.im = im[i];
	z.re = re[i];
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && iteration <= control->max_iterations)
	{
		z1.re = pow(z.re, 2.0) - pow(z.im, 2.0) - re[i];
		z1.im = 2.0 * fabs(z.re * z.im) + im[i];
		z = z1;
		iteration++;
	}
color[i] = ft_get_color(iteration, control->start_color, control->end_color, control->color_mod);
}

__kernel void julia(__global const double *re, __global const double *im, __global int *color, __global t_control *control) 
{
	int i = get_global_id(0);
	int iteration;
	t_complex z;
	t_complex z1;
	
	iteration = 0;
	z.im = im[i];
	z.re = re[i];
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && iteration <= control->max_iterations)
	{
		z1.re = pow(z.re, 2.0) - pow(z.im, 2.0) + control->c.re;
		z1.im = 2.0 * z.re * z.im + control->c.im;
		z = z1;
		iteration++;
	}
color[i] = ft_get_color(iteration, control->start_color, control->end_color, control->color_mod);
}

__kernel void newton(__global const double *re, __global const double *im, __global int *color, __global t_control *control) 
{
	int i = get_global_id(0);
	int iteration;
	t_complex z;
	t_complex z1;
	t_complex d;
	
	iteration = 0;
	z.im = im[i];
	z.re = re[i];
	d = z;
	while (pow(z.re, 2) + pow(z.im, 2) < 1e+6 && pow(d.re, 2) + pow(d.im, 2) > 1e-6 && iteration <= control->max_iterations)
	{
		z1.re = 2.0 / 3 * z.re + (pow(z.re, 2) - pow(z.im, 2)) / (3.0 * (pow(pow(z.re, 2) + pow(z.im, 2), 2)));
		z1.im = 2.0 / 3 * z.im * (1 - z.re / (pow(pow(z.re, 2) + pow(z.im, 2), 2)));
		d.re = fabs(z.re - z1.re);
		d.im = fabs(z.im - z1.im);
		z = z1;
		iteration++;
	}
color[i] = ft_get_color(iteration, control->start_color, control->end_color, control->color_mod);
}