#include "structures_bonus.h"
#include "utils_bonus.h"
#include "trace_bonus.h"

t_color3	pl_get_albedo(t_plain *pl, t_hit_record *rec, t_object *pl_obj)
{
	t_vec3	local_p;
	double	u;
	double	v;

	if (pl_obj->cd == 0)
		return (pl_obj->albedo);
	local_p = vminus(rec->p, pl->p);
	u = vdot(local_p, pl->vecu);
	v = vdot(local_p, pl->vecv);
	if ((int)(floor(u * PLAIN_CHECKER_WIDTH) \
		+ floor(v * PLAIN_CHECKER_HEIGHT)) % 2 == 0)
		return (color3(0.0, 0.0, 0.0));
	else
		return (color3(1.0, 1.0, 1.0));
}

t_bool	hit_plain(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plain	*pl;
	double	root;
	double	root_numerator;
	double	root_denominator;

	pl = pl_obj->element;
	root_denominator = vdot(pl->n, ray->dir);
	if (check_eql_double(root_denominator, 0))
		return (FALSE);
	root_numerator = vdot(pl->n, vminus(pl->p, ray->orig));
	root = root_numerator / root_denominator;
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = pl->n;
	set_face_normal(ray, rec);
	rec->albedo = pl_get_albedo(pl, rec, pl_obj);
	return (TRUE);
}
