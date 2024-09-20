#include "structures_bonus.h"
#include "utils_bonus.h"
#include "trace_bonus.h"

t_color3	cy_get_albedo(t_cylinder *cy, t_object *cy_obj)
{
	t_vec3	proj;
	double	u;
	double	v;

	if (cy_obj->cd == 0)
		return (cy_obj->albedo);
	proj = vminus(cy->pc, vscalar(cy->n, vdot(cy->pc, cy->n)));
	u = 0.5 + atan2(proj.z, proj.x) / (2.0 * M_PI);
	v = cy->pc_doc_hhat / cy->height;
	if ((int)(floor(u * CHECKER_TIMES) \
		+ floor(v * CHECKER_TIMES)) % 2 == 0)
		return (color3(0.0, 0.0, 0.0));
	else
		return (color3(1.0, 1.0, 1.0));
}

t_bool	has_cylinder_root(t_eql *eql, t_ray *ray, t_cylinder *cy)
{
	const t_vec3	w = vminus(ray->orig, cy->center);
	const double	v_dot_hhat = vdot(ray->dir, cy->n);
	const double	w_dot_hhat = vdot(w, cy->n);

	eql->a = vdot(ray->dir, ray->dir) - v_dot_hhat * v_dot_hhat;
	eql->half_b = vdot(ray->dir, w) - v_dot_hhat * w_dot_hhat;
	eql->c = vdot(w, w) - w_dot_hhat * w_dot_hhat - cy->radius * cy->radius;
	eql->discriminant = eql->half_b * eql->half_b - eql->a * eql->c;
	if (eql->discriminant < 0)
		return (FALSE);
	eql->sqrtd = sqrt(eql->discriminant);
	eql->root1 = (-eql->half_b - eql->sqrtd) / eql->a;
	eql->root2 = (-eql->half_b + eql->sqrtd) / eql->a;
	return (TRUE);
}

t_bool	check_cylinder_height(t_cylinder *cy, \
	t_ray *ray, double root, t_hit_record *rec)
{
	rec->t = root;
	rec->p = ray_at(ray, root);
	cy->pc = vminus(rec->p, cy->center);
	cy->pc_doc_hhat = vdot(cy->pc, cy->n);
	rec->normal = vdivide(vminus(cy->pc, \
		vscalar(cy->n, cy->pc_doc_hhat)), cy->radius);
	return (cy->pc_doc_hhat < EPSILON || cy->height < cy->pc_doc_hhat);
}

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_eql		eql;

	cy = cy_obj->element;
	ft_memset(&eql, 0, sizeof(t_eql));
	if (has_cylinder_root(&eql, ray, cy) == FALSE)
		return (FALSE);
	if (eql.root1 < rec->tmin || rec->tmax < eql.root1
		|| check_cylinder_height(cy, ray, eql.root1, rec))
	{
		if (eql.root2 < rec->tmin || rec->tmax < eql.root2
			|| check_cylinder_height(cy, ray, eql.root2, rec))
			return (FALSE);
	}
	set_face_normal(ray, rec);
	rec->albedo = cy_get_albedo(cy, cy_obj);
	return (TRUE);
}
