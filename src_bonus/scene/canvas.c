#include "scene.h"

t_canvas	canvas(int width, int height, double h_fov)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	canvas.h_fov = to_radians(h_fov);
	printf("h_fov(rad) : %lf\n", canvas.h_fov);
	return (canvas);
}
