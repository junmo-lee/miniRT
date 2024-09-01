#include "../src/structures.h"
#include "../src/scene.h"
#include "../src/utils.h"

// mandatory 부분 붙여넣기

t_cone		*cone(t_point3 center, t_vec3 n, double radius, double height)
{
    t_cone *co;

    if(!(co = (t_cone *)malloc(sizeof(t_cone))))
        return (NULL);
	co->center = center;
	co->n = vunit(n); // 2-norm 이 1인 단위벡터로 변환
	co->radius = radius;
	co->height = height;
	co->h = vmult(co->n, height);
	co->H = vplus(co->center, co->h);
	co->m = pow(co->radius / co->height, 2.0);
    return (co);
}