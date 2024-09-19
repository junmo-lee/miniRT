#ifndef DRAW_BONUS_H
# define DRAW_BONUS_H

# include <stdio.h>
# include "structures.h"

unsigned int	color_to_int(t_color3 pixel_color);
int				draw_img(t_vmlx *mlx);
void			my_mlx_pixel_put(t_vmlx *data, \
int x, int y, unsigned int color);

#endif