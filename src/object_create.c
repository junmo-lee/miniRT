#include "structures.h"
#include "scene.h"
#include "utils.h"

t_object    *object(t_object_type type, void *element, t_color3 albedo)
{
	t_object    *new;

	if (!(new = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	new->type = type;
	new->element = element;
	new->albedo = albedo;
	new->next = NULL;
	return (new);
}

t_sphere    *sphere(t_point3 center, double radius)
{
	t_sphere *sp;

	if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_plain		*plain(t_point3 P, t_vec3 n)
{
    t_plain *pl;

    if(!(pl = (t_plain *)malloc(sizeof(t_plain))))
        return (NULL);
	pl->P = P;
	pl->n = vunit(n); // 처음에 정규화되었는지 확인해야 함, 일단 정규화하는걸로
    return (pl);
}

t_cylinder		*cylinder(t_point3 center, t_vec3 n, double radius, double height)
{
    t_cylinder *cy;

    if(!(cy = (t_cylinder *)malloc(sizeof(t_cylinder))))
        return (NULL);
	cy->center = center;
	cy->n = vunit(n); // 처음에 정규화되었는지 확인해야 함, 일단 정규화하는걸로
	cy->radius = radius;
	cy->height = height;
	cy->h = vmult(cy->n, height);
    return (cy);
}

t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
	t_light *light;

	if(!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}