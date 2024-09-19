#include "structures.h"
#include "scene.h"
#include "utils.h"

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere	*sp;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (sp == NULL)
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_plain	*plain(t_point3 p, t_vec3 n)
{
	t_plain	*pl;

	pl = (t_plain *)malloc(sizeof(t_plain));
	if (pl == NULL)
		return (NULL);
	pl->p = p;
	pl->n = vunit(n);
	pl->vecu = vcross(pl->n, vec3(0, 1, 0));
	if (check_eql_double(vlength(pl->vecu), 0))
		pl->vecu = vcross(pl->n, vec3(1, 0, 0));
	pl->vecu = vunit(pl->vecu);
	pl->vecv = vunit(vcross(pl->n, pl->vecu));
	return (pl);
}

t_cone	*cylinder(t_point3 center, t_vec3 n, double radius, double height)
{
	t_cone	*cy;

	cy = (t_cone *)malloc(sizeof(t_cone));
	if (cy == NULL)
		return (NULL);
	cy->center = center;
	cy->n = vunit(n);
	cy->radius = radius;
	cy->height = height;
	cy->h = vscalar(cy->n, height);
	return (cy);
}

t_light	*light_point(t_point3 light_origin, \
t_color3 light_color, double bright_ratio)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		return (NULL);
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio * LUMEN;
	return (light);
}

t_cone	*cone(t_point3 center, t_vec3 n, double radius, double height)
{
	t_cone	*co;

	co = (t_cone *)malloc(sizeof(t_cone));
	if (co == NULL)
		return (NULL);
	co->center = center;
	co->n = vunit(n);
	co->radius = radius;
	co->height = height;
	co->h = vscalar(co->n, -height);
	co->pointh = vplus(co->center, co->h);
	co->m = pow(co->radius / co->height, 2.0);
	return (co);
}
