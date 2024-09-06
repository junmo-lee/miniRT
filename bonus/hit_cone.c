#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool      hit_cone(t_object *co_obj, t_ray *ray, t_hit_record *rec)
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

	t_vec3	PH;
	double	PH_dot_Hhat;

	co = co_obj->element;
	W = vminus(ray->orig, co->H);
	V_dot_Hhat = vdot(ray->dir, co->n);
	W_dot_Hhat = vdot(W, co->n);

	a = vdot(ray->dir, ray->dir) - (co->m + 1.0) * V_dot_Hhat * V_dot_Hhat;
	b = 2.0 * (vdot(ray->dir, W) - (co->m + 1.0) * V_dot_Hhat * W_dot_Hhat);
	c = vdot(W, W) - (co->m + 1.0) * W_dot_Hhat * W_dot_Hhat;
	D = b * b - (4.0 * a * c);
	// todo : D/2 판별식으로 변환하기, co->m + 1.0 을 미리 계산해놓기

	if (D < 0)
		return (FALSE);
	sqrtD = sqrt(D);

	root = (-b - sqrtD) / (2.0 * a);
	rootP = ray_at(ray, root);
	PH = vminus(rootP, co->H);
	PH_dot_Hhat = vdot(PH, co->n);
	if (root < rec->tmin || rec->tmax < root
		|| PH_dot_Hhat < EPSILON || co->height < PH_dot_Hhat)
	{
		root = (-b + sqrtD) / (2.0 * a);
		rootP = ray_at(ray, root);
		PH = vminus(rootP, co->H);
		PH_dot_Hhat = vdot(PH, co->n);
		if (root < rec->tmin || rec->tmax < root
			|| PH_dot_Hhat < EPSILON || co->height < PH_dot_Hhat)
			return (FALSE);
	}
	rec->t = root;
	rec->p = rootP;
	rec->normal = vminus(PH, vmult(co->n, PH_dot_Hhat));
	set_face_normal(ray, rec);
	rec->albedo = co_obj->albedo;
	return (TRUE);
}