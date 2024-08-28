/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:37:38 by junmlee           #+#    #+#             */
/*   Updated: 2024/06/27 17:21:46 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal_bonus.h"

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	center_move(t_vars *vars)
{
	vars->dx += vars->args->scale * vars->args->cx * KEY_OFFSET;
	vars->dy += vars->args->scale * vars->args->cy * KEY_OFFSET;
}

void	keymove(t_vars *vars)
{
	if (vars->key_move == KEY_X_UP)
		vars->dx -= vars->args->scale * KEY_OFFSET;
	else if (vars->key_move == KEY_X_DOWN)
		vars->dx += vars->args->scale * KEY_OFFSET;
	else if (vars->key_move == KEY_Y_UP)
		vars->dy -= vars->args->scale * KEY_OFFSET;
	else if (vars->key_move == KEY_Y_DOWN)
		vars->dy += vars->args->scale * KEY_OFFSET;
	vars->key_move = KEY_MOVE_NONE;
}

void	zoom(t_vars *vars)
{
	double	mouse_world_x;
	double	mouse_world_y;

	if (vars->zoom_stat == 0)
		return ;
	mouse_world_x = vars->args->scale * (vars->mouse_x - WEIGHT / 2);
	mouse_world_y = vars->args->scale * (vars->mouse_y - HEIGHT / 2);
	if (vars->zoom_stat == ZOOM_UP)
	{
		vars->dx += SCALE_FACTOR * mouse_world_x;
		vars->dy += SCALE_FACTOR * mouse_world_y;
		vars->args->scale *= (1 - SCALE_FACTOR);
	}
	else if (vars->zoom_stat == ZOOM_DOWN)
	{
		vars->dx -= SCALE_FACTOR * mouse_world_x;
		vars->dy -= SCALE_FACTOR * mouse_world_y;
		vars->args->scale *= (1 + SCALE_FACTOR);
	}
}

void	draw_loop(t_vars *vars)
{
	int	i;
	int	j;

	mlx_clear_window(vars->mlx, vars->win);
	keymove(vars);
	zoom(vars);
	i = 0;
	while (i < WEIGHT)
	{
		j = 0;
		while (j < HEIGHT)
		{
			vars->fractal_f(vars, vars->args, i, j);
			j++;
		}
		i++;
	}
	vars->zoom_stat = ZOOM_NONE;
}
