#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"
#include "parse.h"

void	leaks_check(void)
{
	system("leaks debug.out");
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


void	print_ksn(char *type, double ksn)
{
	printf ("\n\n\n");
	printf("%s : ", type);
	printf("%f\n\n", ksn);
}

void	print_cd(char *type, int cd)
{
	printf ("\n\n\n");
	printf("%s : ", type);
	printf("%d\n\n", cd);
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

	// check parse
	t_ambient_p *a_ptr = parsed_struct.ambient_pointer;
	printf("ambient ratio : %.4lf\n", a_ptr->ratio);

	t_camera_p *c_ptr = parsed_struct.camera_pointer;
	printf("camera c : "); vprint(c_ptr->coordinates);
	printf("camera n : "); vprint(c_ptr->normal_vector);
	printf("camera fov : %d\n", c_ptr->fov);

	// light 테스트
	print_light(&parsed_struct);

	// ksn cd 테스트
	if (parsed_struct.object_pointer->cone != NULL)
	{
		print_ksn("cone", parsed_struct.object_pointer->cone->ksn);
		print_cd("cone", parsed_struct.object_pointer->cone->cd);
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
	return (0);
}


// int main(void)
// {
// 	t_vec3 a = vec3(1.0, 2.0, 1.0);
// 	t_vec3 b = vec3(1.0, -2.0, 1.0);

// 	t_vec3 c = vplus(a, b);
// 	(void)c;
// }