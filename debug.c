#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"
#include "parse.h"

// void	leaks_check(void)
// {
// 	system("leaks debug.out");
// }

int	main(int argc, char **argv)
{
	t_parse parsed_struct; // malloc을 최소화 하려함

	// atexit(leaks_check);
	if (argc != 2)
	{
		printf("argument error\n");
		return (0);
	}
	else
	{
		parse(&parsed_struct, argv[1]);
	}

	// in src/main.c
	t_vmlx		vmlx;

	// vmlx.scene = scene_init();
	vmlx.scene = parse_to_scene(&parsed_struct);
	make_window(&vmlx);

	draw_img(&vmlx);
	mlx_put_image_to_window(vmlx.mlx, vmlx.win, vmlx.img, 0, 0);
	mlx_hook(vmlx.win, ON_DESTROY, 0, normal_exit, &vmlx);
	mlx_hook(vmlx.win, ON_KEYUP, 0, key_press, &vmlx);
	mlx_loop(vmlx.mlx);
	mlx_destroy_window(vmlx.mlx, vmlx.win);
	return (0);
}


// int main(void)
// {
// 	t_vec3 a = vec3(1.0, 2.0, 1.0);
// 	t_vec3 b = vec3(1.0, -2.0, 1.0);

// 	t_vec3 c = vplus(a, b);
// 	(void)c;
// }