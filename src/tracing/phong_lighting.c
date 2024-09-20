#include "trace.h"

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color3(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vplus(light_color, \
				point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = vplus(light_color, scene->ambient);
	return (vmin(vmulti(light_color, scene->rec.albedo), color3(1, 1, 1)));
}

t_color3	point_light_get(t_scene *scene, t_light *light)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	t_ray		light_ray;

	light_dir = vminus(light->origin, scene->rec.p);
	light_ray = ray(vplus(scene->rec.p, \
		vscalar(scene->rec.normal, EPSILON)), light_dir);
	if (in_shadow(scene->world, light_ray, vlength(light_dir)))
		return (color3(0, 0, 0));
	light_dir = vunit(light_dir);
	diffuse = vscalar(light->light_color, \
		fmax(vdot(scene->rec.normal, light_dir), 0.0));
	return (vscalar(diffuse, light->bright_ratio));
}

t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}
