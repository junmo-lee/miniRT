#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"

int	error_exit(t_vmlx *vmlx)
{
	mlx_destroy_window(vmlx->mlx, vmlx->win);
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}
int	normal_exit(t_vmlx *vmlx)
{
	mlx_destroy_window(vmlx->mlx, vmlx->win);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	key_press(int keycode, t_vmlx *vmlx)
{
	if (keycode == KCODE_ESC)
		normal_exit(vmlx);
	else
		return (0);
	mlx_put_image_to_window(vmlx->mlx, vmlx->win, vmlx->img, 0, 0);
	return (0);
}

int	make_window(t_vmlx	*vmlx)
{
	vmlx->mlx = mlx_init();
	if (vmlx->mlx == NULL)
		exit(1);
	vmlx->win = mlx_new_window(vmlx->mlx, R_WIDTH, R_HIGHT, WIN_NAME);
	vmlx->img = mlx_new_image(vmlx->mlx, R_WIDTH, R_HIGHT);
	vmlx->addr = mlx_get_data_addr(vmlx->img, \
		&(vmlx->bits_per_pixel), &(vmlx->line_length), &(vmlx->endian));
	if (vmlx->win == NULL || vmlx->img == NULL || vmlx->addr == NULL)
		error_exit(vmlx);
	return (EXIT_SUCCESS);
}