#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"

const t_point3	EXAMPLE_ORIGIN = {EXAMPLE_OX, EXAMPLE_OY, EXAMPLE_OZ};
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
					light_point(point3(0, 5, 0), color3(0, 1, 0), EXAMPLE_BRIGHT_RATIO), 
					color3(0, 0, 0)
				);
	oadd(&lights, object(LIGHT_POINT, 
					light_point(point3(0, 5, 0), color3(1, 0, 0), EXAMPLE_BRIGHT_RATIO), 
					color3(0, 0, 0)
				)
	);
	oadd(&lights, object(LIGHT_POINT, 
					light_point(point3(0, 5, 0), color3(0, 0, 1), EXAMPLE_BRIGHT_RATIO), 
					color3(0, 0, 0)
				)
	);

	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmult(color3(1,1,1), ka);

	return (scene);
}


t_scene *parse_to_scene(t_parse* parsed)
{
	t_scene     *scene;
	t_object    *world;
	t_object    *lights;
	double      ka;

	// malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);

	// check parse
	t_ambient_p *a_ptr = parsed->ambient_pointer;
	printf("ambient ratio : %.4lf\n", a_ptr->ratio);

	t_camera_p *c_ptr = parsed->camera_pointer;
	printf("camera c : "); vprint(c_ptr->coordinates);
	printf("camera n : "); vprint(c_ptr->normal_vector);
	printf("camera fov : %d\n", c_ptr->fov);
	scene->canvas = canvas(R_WIDTH, R_HIGHT, c_ptr->fov);
	scene->camera = camera(&scene->canvas, c_ptr->coordinates, vunit(c_ptr->normal_vector));

	t_light_p *l_ptr = parsed->light_pointer;
	printf("light pos : "); vprint(l_ptr->coordinates);
	printf("light c : "); vprint(l_ptr->colors);
	printf("light b : %.4lf\n", l_ptr->brightness);

	ft_memset(&world, 0, sizeof(world));
	world = object(NONE, NULL, color3(0, 0, 0));

	t_object_p *o_ptr = parsed->object_pointer;
	while (o_ptr != NULL)
	{
		switch (o_ptr->identifier)
		{
			case SP:
				printf("SP : \n");
				printf("pos : "); vprint(o_ptr->sphere->coordinates);
				printf("r : %.4lf \n", o_ptr->sphere->diameter);
				printf("color : "); vprint(o_ptr->sphere->colors);
				oadd(&world, object(SP, sphere(o_ptr->sphere->coordinates, o_ptr->sphere->diameter), vdivide(o_ptr->sphere->colors, RGB_MAX)));
				break;
			case PL:
				printf("PL : \n");
				printf("pos : "); vprint(o_ptr->plane->coordinates);
				printf("n : "); vprint(o_ptr->plane->normal_vector);
				printf("color : "); vprint(o_ptr->plane->colors);
				oadd(&world, object(PL, plain(o_ptr->plane->coordinates, o_ptr->plane->normal_vector), vdivide(o_ptr->plane->colors, RGB_MAX)));
				break;
			case CY:
				printf("CY : \n");
				printf("pos : "); vprint(o_ptr->cylinder->coordinates);
				printf("n : "); vprint(o_ptr->cylinder->normal_vector);
				printf("r : %.4lf \n", o_ptr->cylinder->diameter);
				printf("h : %.4lf \n", o_ptr->cylinder->height);
				printf("color : "); vprint(o_ptr->cylinder->colors);
				oadd(&world, object(CY, cylinder(o_ptr->cylinder->coordinates, o_ptr->cylinder->normal_vector, o_ptr->cylinder->diameter, o_ptr->cylinder->height), vdivide(o_ptr->cylinder->colors, RGB_MAX)));
				break; 
			case CO:
				printf("CO : \n");
				printf("pos : "); vprint(o_ptr->cone->coordinates);
				printf("n : "); vprint(o_ptr->cone->normal_vector);
				printf("r : %.4lf \n", o_ptr->cone->diameter);
				printf("h : %.4lf \n", o_ptr->cone->height);
				printf("color : "); vprint(o_ptr->cone->colors);
				oadd(&world, object(CO, cone(o_ptr->cone->coordinates, o_ptr->cone->normal_vector, o_ptr->cone->diameter, o_ptr->cone->height), vdivide(o_ptr->cone->colors, RGB_MAX)));
				break;
			default :
				printf("NONE\n");
				break;
		}
		o_ptr = o_ptr->next;
	}
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