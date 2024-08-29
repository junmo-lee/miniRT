#include "scene.h"

const t_vec3	UP_VECTOR = {0, 1, 0};

t_camera    camera(t_canvas *canvas, t_point3 orig, t_point3 camera_direction)
{
	t_camera    cam;
	t_vec3      FcrossUP;
	// double      focal_len;
	// double      viewport_height;

	// viewport_height = 2.0;
	// focal_len = 1.0;
	cam.orig = orig;
	cam.camera_direction = camera_direction;
	cam.viewport_h = canvas->height;
	// cam.viewport_w = viewport_height * canvas->aspect_ratio;
	cam.viewport_w = canvas->width;
	// cam.focal_len = focal_len;
	cam.focal_len = (double)canvas->width / (2 * tan(canvas->fov / 2));
	fprintf(stderr, "forcal_len : %.4lf\n", cam.focal_len);
	cam.vertical = vmult(UP_VECTOR, cam.viewport_h); // up vector 에 height를 곱해놓음 회전시에 바꾸면 될듯?
	// cam.horizontal = vec3(cam.viewport_w, 0, 0);
	// horizontal = F(ront Vector, D) X Up(0, 1, 0)
	// camera_direction 과 Up vector 의 각이 
	//  0(0, 1, 0), PI(0, -1, 0) 일떄 sin 이 0이 되면서 수평방향이 영벡터가 됨(짐벌 락)
	//  0(0, 1, 0) : (1, 0, 0), PI(0, -1, 0) : (-1, 0, 0) 으로 수동 지정
	FcrossUP = vcross(cam.camera_direction, UP_VECTOR);
	if (vlength(FcrossUP) == 0)
	{
		if (check_eql_double(vangle(cam.camera_direction, UP_VECTOR), 0))
			FcrossUP = vec3(1, 0, 0);
		else
			FcrossUP = vec3(-1, 0, 0);
	}
	cam.horizontal = vmult(vunit(FcrossUP), cam.viewport_w);
	vprint(cam.horizontal);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam.left_bottom = vminus(
						vminus(
							vminus(
								cam.orig, 
								vdivide(cam.horizontal, 2)),
			  				vdivide(cam.vertical, 2)), 
						vec3(0, 0, cam.focal_len));
	return (cam);
}