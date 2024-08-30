#include "structures.h"
#include "print.h"
#include "trace.h"
#include "scene.h"

const t_point3	EXAMPLE_ORIGIN = {0, 0, 0};
const t_vec3	EXAMPLE_DIRECTION = {EXAMPLE_DX, EXAMPLE_DY, EXAMPLE_DZ};

t_scene *scene_init(void)
{
	t_scene     *scene;
	t_object    *world;
	t_object    *lights;
	double      ka;

	// malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	scene->canvas = canvas(R_WIDTH, R_HIGHT, EXAMPLE_FOV);
	scene->camera = camera(&scene->canvas, EXAMPLE_ORIGIN, EXAMPLE_DIRECTION);
	world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); // world 에 구1 추가
	oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); // world 에 구2 추가
	//oadd(&world, object(SP, sphere(point3(0, -1000, 0), 990), color3(1, 1, 1))); // world 에 구3 추가
	// Modify junmlee at 8/28, 평면이 없어 구를 늘려 예제와 비슷하게 구현
	// oadd(&world, object(SP, sphere(point3(0, -10000, 0), 9990), color3(1, 1, 1)));
	// oadd(&world, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1))); // world 에 구3 추가
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(point3(0, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
	// lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmult(color3(1,1,1), ka);
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

	scene = scene_init();
	// 랜더링
	// P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
	printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
	j = scene->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			//ray from camera origin to pixel
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene);
			// ray_color함수의 인자도 ray, world를 모두 담고 있는 scene으로 바꿨다.
			write_color(pixel_color);
			++i;
		}
		--j;
	}
	return (0);
}