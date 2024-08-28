/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:33:24 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/28 14:16:34 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal_bonus.h"

int	error_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(1);
	return (1);
}

int	normal_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KCODE_ESC)
		normal_exit(vars);
	else if (keycode == KCODE_LEFT_ARROW)
		vars->key_move = KEY_X_UP;
	else if (keycode == KCODE_RIGHT_ARROW)
		vars->key_move = KEY_X_DOWN;
	else if (keycode == KCODE_UP_ARROW)
		vars->key_move = KEY_Y_UP;
	else if (keycode == KCODE_DOWN_ARROW)
		vars->key_move = KEY_Y_DOWN;
	else
	{
		vars->key_move = KEY_MOVE_NONE;
		return (0);
	}
	draw_loop(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	mouse_down(int butten, int x, int y, t_vars *vars)
{
	vars->mouse_x = x;
	vars->mouse_y = y;
	if (butten == MCODE_SCROLLUP)
		vars->zoom_stat = ZOOM_UP;
	else if (butten == MCODE_SCROLLDOWN)
		vars->zoom_stat = ZOOM_DOWN;
	else
	{
		vars->zoom_stat = ZOOM_NONE;
		return (0);
	}
	draw_loop(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args	args;
	t_vars	vars;
	int		color_map[ITER_MAX];

	init(&vars, &args);
	if (parsing(&args, argc, argv))
		exit(1);
	args_config(&vars);
	vars.color_map = color_map;
	if (make_colormap(&args, color_map))
		error_exit(&vars);
	draw_loop(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_hook(vars.win, ON_MOUSEDOWN, 0, mouse_down, &vars);
	mlx_hook(vars.win, ON_KEYUP, 0, key_press, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, normal_exit, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	return (0);
}
