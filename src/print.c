#include "print.h"

double clamp(double x)
{
	if (x < 0.0)
		return (0.0);
	if (x > 1.0)
		return (1.0);
	return (x);
}

// [0,1] 로 되어있는 rgb 값을 각각 [0,255]에 맵핑 해서 출력.
void    write_color(t_color3 pixel_color)
{
	printf("%d %d %d\n", (int)(255.999 * clamp(pixel_color.x)),
		(int)(255.999 * clamp(pixel_color.y)),
		(int)(255.999 * clamp(pixel_color.z)));
}