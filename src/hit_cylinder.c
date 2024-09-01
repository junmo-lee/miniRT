#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool		in_cylinder_h(t_point3 rootP, t_cylinder *cy)
{
	t_vec3	in_cy;
	double	check_h;

	in_cy = vminus(rootP, cy->center);
	check_h = vdot(in_cy, cy->h);
	return (EPSILON < check_h && check_h < cy->height);
}

t_bool      hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
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

	t_vec3	PC;
	double	PC_dot_Hhat;

	cy = cy_obj->element;
	W = vminus(ray->orig, cy->center);
	V_dot_Hhat = vdot(ray->dir, cy->n);
	W_dot_Hhat = vdot(W, cy->n);

	a = vdot(ray->dir, ray->dir) - V_dot_Hhat * V_dot_Hhat;
	b = 2.0 * (vdot(ray->dir, W) - V_dot_Hhat * W_dot_Hhat);
	c = vdot(W, W) - W_dot_Hhat * W_dot_Hhat - cy->radius * cy->radius;

	D = b * b - (4.0 * a * c);
	// todo : D/2 판별식으로 변환하기

	if (D < 0)
		return (FALSE);
	sqrtD = sqrt(D);

	root = (-b - sqrtD) / (2.0 * a);
	rootP = ray_at(ray, root);
	PC = vminus(rootP, cy->center);
	PC_dot_Hhat = vdot(PC, cy->n);
	if (root < rec->tmin || rec->tmax < root
		|| PC_dot_Hhat < EPSILON || cy->height < PC_dot_Hhat)
	{
		root = (-b + sqrtD) / (2.0 * a);
		rootP = ray_at(ray, root);
		PC = vminus(rootP, cy->center);
		PC_dot_Hhat = vdot(PC, cy->n);
		if (root < rec->tmin || rec->tmax < root
			|| PC_dot_Hhat < EPSILON || cy->height < PC_dot_Hhat)
			return (FALSE);
	}
	rec->t = root;
	rec->p = rootP;
	rec->normal = vdivide(vminus(PC, vmult(cy->n,PC_dot_Hhat)), cy->radius);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}