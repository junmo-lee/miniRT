#include "scene.h"

t_canvas    canvas(int  width, int height, int fov)
{
    t_canvas canvas;

    canvas.width = width;
    canvas.height = height;
    canvas.aspect_ratio = (double)width / (double)height;
    canvas.fov = to_radians(fov);
    return (canvas);
}