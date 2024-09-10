#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool      hit_plain(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plain	*pl;
	double	root;
	double	root_numerator;
	double	root_denominator;

	pl = pl_obj->element;
	root_denominator = vdot(pl->n, ray->dir);
	if (check_eql_double(root_denominator,  0)) // 분모가 0이 되는 경우
		return (FALSE);
	root_numerator = vdot(pl->n, vminus(pl->P, ray->orig));
	root = root_numerator / root_denominator;
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = pl->n;
	set_face_normal(ray, rec);
	rec->albedo = pl_obj->albedo;
	return (TRUE);
}