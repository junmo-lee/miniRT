#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool      hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere *sp;
	t_vec3  oc;
	double  a;
	//b를 half_b로 변경
	double  half_b;
	double  c;
	double  discriminant; //판별식
	double  sqrtd;
	double  root;

	sp = sp_obj->element;
	oc = vminus(ray->orig, sp->center);
	a = vdot(ray->dir, ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vdot(oc, oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); // 정규화된 법선 벡터.
	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
	rec->albedo = sp_obj->albedo;
	return (TRUE);
}
