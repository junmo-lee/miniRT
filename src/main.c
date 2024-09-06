#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"

# define R_WIDTH 600
# define R_HIGHT 600

#define EXAMPLE_OX 2
#define EXAMPLE_OY 0
#define EXAMPLE_OZ 0

#define EXAMPLE_BRIGHT_RATIO 0.8

// 예제에서는 (1, 0, 0) 이 수평방향(오른쪽) 이 되도록, D = (0, Dy, -1) 꼴이어야 함  
# define EXAMPLE_DX 0
# define EXAMPLE_DY 0 // Dy
# define EXAMPLE_DZ -1
# define EXAMPLE_H_FOV 120

const t_point3	EXAMPLE_ORIGIN = {EXAMPLE_OX, EXAMPLE_OY, EXAMPLE_OZ};
const t_vec3	EXAMPLE_DIRECTION = {EXAMPLE_DX, EXAMPLE_DY, EXAMPLE_DZ};

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

t_scene *scene_init(void)
{
	t_scene     *scene;
	t_object    *world;
	t_object    *lights;
	double      ka;

	// malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	scene->canvas = canvas(R_WIDTH, R_HIGHT, EXAMPLE_H_FOV);
	scene->camera = camera(&scene->canvas, EXAMPLE_ORIGIN, EXAMPLE_DIRECTION);
	// world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0));
	// oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));

	// xyz 좌표 확인용
	// oadd(&world, object(SP, sphere(point3(-2, 0, 0), 1), color3(1, 0, 0)));
	// oadd(&world, object(SP, sphere(point3(0, -2, 0), 1), color3(0, 1, 0)));
	// oadd(&world, object(SP, sphere(point3(0, 0, -2), 1), color3(0, 0, 1)));

	// oadd(&world, object(PL, plain(point3(0, -3, 0), vec3(0, 1, 0)), color3(1, 1, 1)));
	world = object(PL, plain(point3(0, -3, 0), vec3(0, 1, 0)), color3(1, 1, 1));
	// oadd(&world, object(CY, cylinder(point3(3, 0, 0), vec3(0, 1, 0), 1, 2), color3(1.0, 0, 0)));
	// oadd(&world, object(CY, cylinder(point3(0, 3, 0), vec3(0, 1, 0), 1, 2), color3(0, 1.0, 0)));
	// oadd(&world, object(CY, cylinder(point3(0, 0, -3), vec3(0, 1, 0), 1, 2), color3(0, 0, 1.0)));

	// oadd(&world, object(CO, cone(point3(-3, 2, 0), vec3(0, -1, 0), 3, 3), color3(1.0, 0, 0)));
	// oadd(&world, object(CO, cone(point3(0, 2, -5), vec3(0, -1, 0), 1, 2), color3(0, 1.0, 0)));
	oadd(&world, object(CO, cone(point3(0, 2, -3), vec3(0, -1, 0), 1, 2), color3(0, 0, 1.0)));

	scene->world = world;
	lights = object(LIGHT_POINT, 
					light_point(point3(0, 5, 0), color3(1, 1, 1), EXAMPLE_BRIGHT_RATIO), 
					color3(0, 0, 0)
				);
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmult(color3(1,1,1), ka);

	return (scene);
}

int	args_config(t_vmlx	*vmlx)
{
	vmlx->mlx = mlx_init();
	if (vmlx->mlx == NULL)
		exit(1);
	vmlx->win = mlx_new_window(vmlx->mlx, R_WIDTH, R_HIGHT, "miniRT");
	vmlx->img = mlx_new_image(vmlx->mlx, R_WIDTH, R_HIGHT);
	vmlx->addr = mlx_get_data_addr(vmlx->img, \
		&(vmlx->bits_per_pixel), &(vmlx->line_length), &(vmlx->endian));
	if (vmlx->win == NULL || vmlx->img == NULL || vmlx->addr == NULL)
		error_exit(vmlx);
	return (EXIT_SUCCESS);
}

int     main(void)
{
	t_vmlx		vmlx;
	vmlx.scene = scene_init();
	args_config(&vmlx);

	draw_img(&vmlx);
	mlx_put_image_to_window(vmlx.mlx, vmlx.win, vmlx.img, 0, 0);
	mlx_hook(vmlx.win, ON_DESTROY, 0, normal_exit, &vmlx);
	mlx_hook(vmlx.win, ON_KEYUP, 0, key_press, &vmlx);
	mlx_loop(vmlx.mlx);
	mlx_destroy_window(vmlx.mlx, vmlx.win);
	return (0);
}