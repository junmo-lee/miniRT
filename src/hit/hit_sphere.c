#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	has_sphere_root(t_eql *eql, t_vec3 dir, t_vec3 oc, double r)
{
	eql->a = vdot(dir, dir);
	eql->half_b = vdot(oc, dir);
	eql->c = vdot(oc, oc) - r;
	eql->discriminant = eql->half_b * eql->half_b - eql->a * eql->c;
	if (eql->discriminant < 0)
		return (FALSE);
	eql->sqrtd = sqrt(eql->discriminant);
	eql->root1 = (-eql->half_b - eql->sqrtd) / eql->a;
	eql->root2 = (-eql->half_b - eql->sqrtd) / eql->a;
	return (TRUE);
}

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_vec3		oc;
	t_eql		eql;

	sp = sp_obj->element;
	oc = vminus(ray->orig, sp->center);
	ft_memset(&eql, 0, sizeof(t_eql));
	if (has_sphere_root(&eql, ray->dir, oc, sp->radius2) == FALSE)
		return (FALSE);
	if (eql.root1 < rec->tmin || rec->tmax < eql.root1)
	{
		rec->t = eql.root2;
		if (eql.root2 < rec->tmin || rec->tmax < eql.root2)
			return (FALSE);
	}
	else
		rec->t = eql.root1;
	rec->p = ray_at(ray, rec->t);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->albedo = sp_obj->albedo;
	return (TRUE);
}
