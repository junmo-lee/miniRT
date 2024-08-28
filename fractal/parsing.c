/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:20:28 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/28 14:16:34 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	print_help(void)
{
	write(STDOUT_FILENO, "----read me!----\n", 18);
	write(STDOUT_FILENO, "1. Type of fractal(Required)\n", 30);
	write(STDOUT_FILENO, " 0 : julia set\n", 16);
	write(STDOUT_FILENO, " 1 : mandelbrot set\n", 21);
	write(STDOUT_FILENO, " 2 : burning ship set\n", 23);
	write(STDOUT_FILENO, "2, 3. cx, cy\n", 14);
	write(STDOUT_FILENO, "4. start scale(positive)\n", 26);
	write(STDOUT_FILENO, "5. divergence threshold(positive)\n", 35);
	write(STDOUT_FILENO, "6, 7. color_start, color_end(0~255)\n", 37);
	write(STDOUT_FILENO, "정수값만 허용, ARGS_DIV로 나뉘어짐\n", 47);
	write(STDOUT_FILENO, "없는 인자들의 기본값 : 0 -7453 1313 10 4 0 255\n", 57);
	write(STDOUT_FILENO, "이후 인자들은 무시\n", 28);
	return (1);
}

int	parsing(t_args *args, int argc, char *argv[])
{	
	if (ARGS_DIV == 0)
		return (1);
	if (argc == 1)
		return (print_help());
	if (atoi_check_num(argv[1], &(args->type)) == 0 \
		|| 0 > args->type || args->type > 2)
		return (print_help());
	if (argc > 2)
		if (atoi_double_check_num(argv[2], &(args->cx)) == 0)
			return (print_help());
	if (argc > 3)
		if (atoi_double_check_num(argv[3], &args->cy) == 0)
			return (print_help());
	if (argc > 4)
		if (atoi_double_check_num(argv[4], &(args->scale)) == 0 \
		|| args->scale <= 0)
			return (print_help());
	if (argc > 5)
		if (atoi_double_check_num(argv[5], &(args->threshold)) == 0 \
		|| args->threshold <= 0)
			return (print_help());
	return (parsing2(args, argc, argv));
}

int	parsing2(t_args *args, int argc, char *argv[])
{
	if (argc > 6)
		if (atoi_check_num(argv[6], &(args->color_start)) == 0 \
			|| 0 > args->color_start || args->color_start > RGB_MAX)
			return (print_help());
	if (argc > 7)
		if (atoi_check_num(argv[7], &(args->color_end)) == 0 \
			|| 0 > args->color_end || args->color_end > RGB_MAX)
			return (print_help());
	return (0);
}

int	args_config(t_vars	*vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		exit(1);
	vars->win = mlx_new_window(vars->mlx, WEIGHT, HEIGHT, "fractal");
	vars->img = mlx_new_image(vars->mlx, WEIGHT, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, \
		&(vars->bits_per_pixel), &(vars->line_length), &(vars->endian));
	if (vars->win == NULL || vars->img == NULL || vars->addr == NULL)
		error_exit(vars);
	vars->args->scale /= ARGS_DIV;
	vars->args->cx /= ARGS_DIV;
	vars->args->cy /= ARGS_DIV;
	if (vars->args->type == 0)
		vars->fractal_f = julia_point;
	else if (vars->args->type == 1)
		vars->fractal_f = mandelbrot_point;
	else if (vars->args->type == 2)
		vars->fractal_f = burning_ship_point;
	if (vars->args->type == 1 || vars->args->type == 2)
		center_move(vars);
	return (0);
}
