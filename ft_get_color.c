/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:33:18 by majosue           #+#    #+#             */
/*   Updated: 2020/03/07 10:04:14 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double			percent(int start, int end, int current)
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

int			ft_set_light(double percentage)
{
	t_colour start;
	t_colour end;
	t_colour result;

	start.composite = START_COLOUR;
	end.composite = END_COLOUR;
	result.color[0] = get_light((start.color)[0], (end.color)[0], percentage);
	result.color[1] = get_light((start.color)[1], (end.color)[1], percentage);
	result.color[2] = get_light((start.color)[2], (end.color)[2], percentage);
   	result.color[3] = 0;
    return (result.composite);
}


int			ft_get_color(t_mlx *mlx, int current)
{
	int		color;
	double	p;
	int start;
	int end;
	int max;
	t_colour c;
	
	start = 0;
	max = MAX_ITERATIONS;
	end = (max - start) / 2;
	
	
	c.color[0] = current * 10;
	c.color[1] = current * 50;
	c.color[2] = current * 110;
	return (c.composite);


	/* while  (end < max - 1)
	{
	//	printf("start %d end %d current %d\n", start, end, current);
		if (current >= start && current < end)
		{
			p = percent(end, start, current);
			color = ft_set_light(p);
			return (color);
		}
	start = end;
	end = end + (max - start) / 2;
	}
	return (END_COLOUR); */
/* 	p = percent(start, MAX_ITERATIONS, current);
	color = ft_set_light(p);
	return (color); */
}
// рекурсивно искать в каком промежутке точка и красить