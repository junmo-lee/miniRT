#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"
#include "parse.h"

// 헤더 분리할때 따로 넣기
t_object	*object(t_object_type type, void *element, t_attribute attrib);
void	add_cone(t_object *world, t_object_p *o_ptr);

t_color3	get_ambient(t_ambient_p *a_ptr)
{
	if (a_ptr == NULL)
		return (color3(0, 0, 0));
	printf("ambient color : ");vprint(a_ptr->colors);
	printf("ambient ratio : %.4lf\n", a_ptr->ratio);
	return (vscalar(vdivide(a_ptr->colors, RGB_MAX), a_ptr->ratio));
}

void	get_camera(t_scene *scene, t_camera_p *c_ptr)
{
	printf("camera c : "); vprint(c_ptr->coordinates);
	printf("camera n : "); vprint(c_ptr->normal_vector);
	printf("camera fov : %d\n", c_ptr->fov);
	scene->canvas = canvas(R_WIDTH, R_HIGHT, c_ptr->fov);
	scene->camera = camera(&scene->canvas, c_ptr->coordinates,\
		vunit(c_ptr->normal_vector));
}

t_object	*get_light(t_light_p *l_ptr)
{
	t_attribute	attrib;
	t_object	*node;

	ft_memset(&attrib, 0, sizeof(t_attribute));
	node = object(NONE, NULL, attrib);
	while (l_ptr != NULL)
	{	
		printf("light pos : "); vprint(l_ptr->coordinates);
		printf("light c : "); vprint(l_ptr->colors);
		printf("light b : %.4lf\n", l_ptr->brightness);
		oadd(&node, object(LIGHT_POINT, \
			light_point(l_ptr->coordinates, \
				vdivide(l_ptr->colors, RGB_MAX), l_ptr->brightness), \
					attrib));
		l_ptr = l_ptr->next_light;
	}
	return (node);
}

t_object	*get_world(t_object_p *o_ptr)
{
	t_attribute	attrib;
	t_object	*world;

	ft_memset(&attrib, 0, sizeof(t_attribute));
	world = object(NONE, NULL, attrib);
	while (o_ptr != NULL)
	{
		if (o_ptr->identifier != NONE)
		{
			if (o_ptr->identifier == SP)
				add_sphere(world, o_ptr);
			else if (o_ptr->identifier == PL)
				add_plain(world, o_ptr);
			else if (o_ptr->identifier == CY)
				add_cylinder(world, o_ptr);
			else if (o_ptr->identifier == CO)
				add_cone(world, o_ptr);
		}
		o_ptr = o_ptr->next;
	}
	return (world);
}

t_scene	*parse_to_scene(t_parse *parsed)
{
	t_scene	*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (scene == NULL)
		return (NULL);
	scene->ambient = get_ambient(parsed->ambient_pointer);
	get_camera(scene, parsed->camera_pointer);
	scene->light = get_light(parsed->light_pointer);
	scene->world = get_world(parsed->object_pointer);
	clean_parsed_struct(parsed);
	return (scene);
}
