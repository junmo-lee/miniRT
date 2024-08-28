/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:06:01 by junmlee           #+#    #+#             */
/*   Updated: 2024/06/28 15:30:11 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	burning_ship_point(t_vars *vars, t_args *args, int x, int y)
{
	t_pos	c;
	double	cx;
	double	cy;
	int		iter;

	cx = args->scale * (x - WEIGHT / 2) + vars->dx;
	cy = args->scale * (y - HEIGHT / 2) + vars->dy;
	c.x0 = 0;
	c.y0 = 0;
	iter = 0;
	while (iter < ITER_MAX)
	{
		c.x1 = c.x0 * c.x0 - c.y0 * c.y0 + cx;
		c.y1 = 2 * fabs(c.x0) * fabs(c.y0) + cy;
		if (c.x1 * c.x1 + c.y1 * c.y1 > args->threshold)
		{
			my_mlx_pixel_put(vars, x, y, \
				vars->color_map[iter]);
			return ;
		}
		c.x0 = c.x1;
		c.y0 = c.y1;
		iter++;
	}
	my_mlx_pixel_put(vars, x, y, vars->color_map[ITER_MAX - 1]);
}
