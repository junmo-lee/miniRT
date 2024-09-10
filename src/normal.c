#include "trace.h"

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	if (vdot(r->dir, rec->normal) < 0)
		rec->normal = rec->normal;
	else
		rec->normal = vscalar(rec->normal, -1);
}
