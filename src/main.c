#include "structures.h"
#include "print.h"
#include "trace.h"
#include "scene.h"

# define R_WIDTH 600
# define R_HIGHT 600

#define EXAMPLE_OX 0
#define EXAMPLE_OY 5
#define EXAMPLE_OZ 5

// 예제에서는 (1, 0, 0) 이 수평방향(오른쪽) 이 되도록, D = (0, Dy, -1) 꼴이어야 함  
# define EXAMPLE_DX 0
# define EXAMPLE_DY 0 // Dy
# define EXAMPLE_DZ -1
# define EXAMPLE_H_FOV 90

const t_point3	EXAMPLE_ORIGIN = {EXAMPLE_OX, EXAMPLE_OY, EXAMPLE_OZ};
const t_vec3	EXAMPLE_DIRECTION = {EXAMPLE_DX, EXAMPLE_DY, EXAMPLE_DZ};

t_scene *scene_init(t_MT19937 *state)
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

	// oadd(&world, object(PL, plain(point3(0, 0, -10), vec3(0, 0, 1)), color3(1, 1, 1)));
	world = object(PL, plain(point3(0, 0, 0), vec3(0, 1, 0)), color3(1, 1, 1));
	oadd(&world, object(CY, cylinder(point3(3, 0, 0), vec3(0, 1, 0), 1, 2), color3(1.0, 0, 0)));
	oadd(&world, object(CY, cylinder(point3(0, 3, 0), vec3(0, 1, 0), 1, 2), color3(0, 1.0, 0)));
	oadd(&world, object(CY, cylinder(point3(0, 0, -3), vec3(0, 1, 0), 1, 2), color3(0, 0, 1.0)));


	scene->world = world;
	lights = object(LIGHT_POINT, light_point(point3(0, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmult(color3(1,1,1), ka);

	// rand init
	init_genrand(state, RAND_SEED);
	return (scene);
}

int     main(void)
{
	int         i;
	int         j;
	double      u;
	double      v;
	t_color3    pixel_color;
	t_scene     *scene;
	t_MT19937	state;
	int			sample;

	scene = scene_init(&state);

	printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
	j = scene->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			sample = 0;
			pixel_color = color3(0, 0, 0);
			while (sample < SAMPLES_PER_PIXEL)
			{
				u = ((double)i + genrand_real3(&state) - 0.5) / (scene->canvas.width - 1);
				v = ((double)j + genrand_real3(&state) - 0.5) / (scene->canvas.height - 1);
				scene->ray = ray_primary(&scene->camera, u, v);
				pixel_color = vplus(pixel_color, ray_color(scene));
				sample++;
			}
			write_color(vmult(pixel_color, 1.0 / SAMPLES_PER_PIXEL));
			++i;
		}
		--j;
	}
	return (0);
}