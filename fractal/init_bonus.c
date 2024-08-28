/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:08:57 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/02 18:07:50 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal_bonus.h"

int	init(t_vars	*vars, t_args *args)
{
	ft_memset(vars, 0, sizeof(t_vars));
	vars->args = args;
	ft_memset(vars->args, 0, sizeof(t_args));
	vars->args->cx = -7453;
	vars->args->cy = 1313;
	vars->args->scale = 10;
	vars->args->threshold = 4;
	vars->args->color_start = 0;
	vars->args->color_end = ITER_MAX - 1;
	vars->args->colormap_type = 0;
	return (0);
}
