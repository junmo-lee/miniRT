#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	has_cone_root(t_eql *eql, t_ray *ray, t_cone *co)
{
	const t_vec3	w = vminus(ray->orig, co->pointh);
	const double	v_dot_hhat = vdot(ray->dir, co->n);
	const double	w_dot_hhat = vdot(w, co->n);

	eql->a = vdot(ray->dir, ray->dir) - (co->m + 1.0) * v_dot_hhat * v_dot_hhat;
	eql->half_b = vdot(ray->dir, w) - (co->m + 1.0) * v_dot_hhat * w_dot_hhat;
	eql->c = vdot(w, w) - (co->m + 1.0) * w_dot_hhat * w_dot_hhat;
	eql->discriminant = eql->half_b * eql->half_b - eql->a * eql->c;
	if (eql->discriminant < 0)
		return (FALSE);
	eql->sqrtd = sqrt(eql->discriminant);
	eql->root1 = (-eql->half_b - eql->sqrtd) / eql->a;
	eql->root2 = (-eql->half_b + eql->sqrtd) / eql->a;
	return (TRUE);
}

t_bool	check_cone_height(t_cone *co, \
	t_ray *ray, double root, t_hit_record *rec)
{
	rec->t = root;
	rec->p = ray_at(ray, root);
	co->ph = vminus(rec->p, co->pointh);
	co->ph_doc_hhat = vdot(co->ph, co->n);
	rec->normal = vminus(co->ph, vscalar(co->n, co->ph_doc_hhat));
	return (co->ph_doc_hhat < EPSILON || co->height < co->ph_doc_hhat);
}

t_bool	hit_cone(t_object *co_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone	*co;
	t_eql	eql;

	co = co_obj->element;
	ft_memset(&eql, 0, sizeof(eql));
	if (has_cone_root(&eql, ray, co) == FALSE)
		return (FALSE);
	if (eql.root1 < rec->tmin || rec->tmax < eql.root1
		|| check_cone_height(co, ray, eql.root1, rec))
	{
		if (eql.root2 < rec->tmin || rec->tmax < eql.root2
			|| check_cone_height(co, ray, eql.root2, rec))
			return (FALSE);
	}
	set_face_normal(ray, rec);
	rec->albedo = co_obj->albedo;
	return (TRUE);
}
