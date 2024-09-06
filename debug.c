#include "src/structures.h"
#include "src/trace.h"
#include "src/scene.h"
#include "src/draw.h"

int main(void)
{
	t_vec3 a = vec3(1.0, 2.0, 1.0);
	t_vec3 b = vec3(1.0, -2.0, 1.0);

	t_vec3 c = vplus(a, b);
	(void)c;
}