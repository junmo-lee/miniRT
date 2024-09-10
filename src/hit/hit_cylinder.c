#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool		hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone	*co;
	t_vec3		W;
	double a;
	double b;
	double c;
	double	D;
	double	V_dot_Hhat;
	double	W_dot_Hhat;
	double	root;
	t_point3	rootP;
	double	sqrtD;

	t_vec3	pc;
	double	pc_doc_hhat;

	co = cy_obj->element;
	W = vminus(ray->orig, co->center);
	V_dot_Hhat = vdot(ray->dir, co->n);
	W_dot_Hhat = vdot(W, co->n);

	a = vdot(ray->dir, ray->dir) - V_dot_Hhat * V_dot_Hhat;
	b = 2.0 * (vdot(ray->dir, W) - V_dot_Hhat * W_dot_Hhat);
	c = vdot(W, W) - W_dot_Hhat * W_dot_Hhat - co->radius * co->radius;

	D = b * b - (4.0 * a * c);
	// todo : D/2 판별식으로 변환하기

	if (D < 0)
		return (FALSE);
	sqrtD = sqrt(D);

	root = (-b - sqrtD) / (2.0 * a);
	rootP = ray_at(ray, root);
	pc = vminus(rootP, co->center);
	pc_doc_hhat = vdot(pc, co->n);
	if (root < rec->tmin || rec->tmax < root
		|| pc_doc_hhat < EPSILON || co->height < pc_doc_hhat)
	{
		root = (-b + sqrtD) / (2.0 * a);
		rootP = ray_at(ray, root);
		pc = vminus(rootP, co->center);
		pc_doc_hhat = vdot(pc, co->n);
		if (root < rec->tmin || rec->tmax < root
			|| pc_doc_hhat < EPSILON || co->height < pc_doc_hhat)
			return (FALSE);
	}
	rec->t = root;
	rec->p = rootP;
	rec->normal = vdivide(vminus(pc, vscalar(co->n,pc_doc_hhat)), co->radius);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}