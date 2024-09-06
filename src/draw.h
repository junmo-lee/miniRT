#ifndef DRAW_H
# define DRAW_H

# include <stdio.h>
# include "structures.h"

unsigned int	color_to_int(t_color3 pixel_color);
// void			my_pixel_put(t_vmlx *mlx, int x, int y, t_MT19937 *state);
void	my_mlx_pixel_put(t_vmlx *data, int x, int y, unsigned int color);
void	my_pixel_put(t_vmlx *vmlx, int i, int j, t_scene *scene);
unsigned int	get_pixel_color(t_scene *scene, int i, int j, t_MT19937 *state);
int				draw_img(t_vmlx *mlx);
void			write_color(t_color3 pixel_color);

#endif