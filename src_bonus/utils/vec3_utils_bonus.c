#include "utils_bonus.h"

void	vprint(t_vec3 vec)
{
	printf("%.4lf %.4lf %.4lf\n", vec.x, vec.y, vec.z);
}

// vec == vec2, vdot = length^2
double	vdot(t_vec3 vec, t_vec3 vec2)
{
	return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

// 벡터 외적
t_vec3	vcross(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}

// 단위 벡터, 영벡터일시 에러출력 및 exit
t_vec3	vunit(t_vec3 vec)
{
	const double	len = vlength(vec);

	if (len == 0)
	{
		printf("Error\n:Devider is 0");
		exit(0);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}
