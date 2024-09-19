#include "trace.h"

// 두 벡터의 원소를 비교하여 작은 값들만 반환
t_vec3	vmin(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vminus(v, vscalar(n, vdot(v, n) * 2.0)));
}
