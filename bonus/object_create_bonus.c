#include "structures.h"
#include "scene.h"
#include "utils.h"

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
