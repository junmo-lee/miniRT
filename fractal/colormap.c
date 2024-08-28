/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colormap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:40:28 by junmlee           #+#    #+#             */
/*   Updated: 2024/06/28 17:20:06 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	trgb(t_args *args, int iter, unsigned char t)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = args->color_start + sin(0.3 * (double)iter) * 32.0;
	g = args->color_start + sin(0.3 * (double)iter) * 127.0;
	b = args->color_start + sin(0.3 * (double)iter) * 64.0;
	return (t << 24 | r << 16 | g << 8 | b);
}

int	make_colormap(t_args *args, int *color_map)
{
	int		i;
	int		n;

	if (ITER_MAX == 0)
		return (1);
	n = args->color_end - args->color_start;
	i = 0;
	while (i < ITER_MAX)
	{
		color_map[i] = trgb(args, n * i / ITER_MAX, RGB_T);
		i++;
	}
	return (0);
}
