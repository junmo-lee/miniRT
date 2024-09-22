#include "structures_bonus.h"
#include "trace_bonus.h"
#include "scene_bonus.h"
#include "draw_bonus.h"
#include "parse_bonus.h"

int	main(int argc, char **argv)
{
	t_parse	parsed_struct;
	t_vmlx	vmlx;

	if (argc != 2)
	{
		printf("argument error\n");
		return (0);
	}
	else
	{
		check_file_name(argv[1]);
		parse(&parsed_struct, argv[1]);
		check_camera_light_bonus(&parsed_struct);
	}
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
