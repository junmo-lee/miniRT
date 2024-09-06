#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"

int     main(void)
{
	t_vmlx		vmlx;
	vmlx.scene = scene_init();
	make_window(&vmlx);

	draw_img(&vmlx);
	mlx_put_image_to_window(vmlx.mlx, vmlx.win, vmlx.img, 0, 0);
	mlx_hook(vmlx.win, ON_DESTROY, 0, normal_exit, &vmlx);
	mlx_hook(vmlx.win, ON_KEYUP, 0, key_press, &vmlx);
	mlx_loop(vmlx.mlx);
	mlx_destroy_window(vmlx.mlx, vmlx.win);
	return (0);
}