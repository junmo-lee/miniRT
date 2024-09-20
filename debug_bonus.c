#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"
#include "parse.h"

# include <time.h>

void	leaks_check(void)
{
	system("leaks debug_bonus.out");
}

void	print_coordinate(t_vec3 xyz)
{
	printf("coordinate : x = %f, y = %f, z = %f\n", xyz.x, xyz.y, xyz.z);
}

void	print_color(t_vec3 xyz)
{
	printf("colors : x = %f, y = %f, z = %f\n", xyz.x, xyz.y, xyz.z);
}

void	print_light(t_parse *parsed_struct)
{
	t_light_p	*current_node;

	current_node = parsed_struct->light_pointer;
	printf("\n\n\n\n linked_light test\n");
	while (current_node != NULL)
	{
		printf("brightness : %f\n", current_node->brightness);
		print_coordinate(current_node->coordinates);
		print_color(current_node->colors);
		printf("\n");
		current_node = current_node->next_light;
	}
	printf("\n\n\n\n");
}

int	main(int argc, char **argv)
{
	t_parse parsed_struct; // malloc을 최소화 하려함

	atexit(leaks_check);
	if (argc != 2)
	{
		printf("argument error\n");
		return (0);
	}
	else
	{
		parse(&parsed_struct, argv[1]);
	}

	print_light(&parsed_struct);
	// in src/main.c
	t_vmlx		vmlx;

	clock_t	start = clock();
	vmlx.scene = parse_to_scene(&parsed_struct);
	make_window(&vmlx);

	draw_img(&vmlx);
	clock_t	end = clock();
	printf("[time : %f]\n", (float)(end - start)/CLOCKS_PER_SEC);
	mlx_put_image_to_window(vmlx.mlx, vmlx.win, vmlx.img, 0, 0);
	mlx_hook(vmlx.win, ON_DESTROY, 0, normal_exit, &vmlx);
	mlx_hook(vmlx.win, ON_KEYUP, 0, key_press, &vmlx);
	mlx_loop(vmlx.mlx);
	mlx_destroy_window(vmlx.mlx, vmlx.win);
	return (0);
}
