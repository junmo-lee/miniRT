#include "scene.h"

const t_vec3	UP_VECTOR = {0, 1, 0};

t_camera    camera(t_canvas *canvas, t_point3 orig, t_point3 camera_direction)
{
	t_camera    cam;
	t_vec3      DcrossUP;
	t_vec3		XcrossD;
	double      focal_len;

	ft_memset(&cam, 0, sizeof(cam));
	focal_len = 1.0; // 1.0 이라고 가정
	cam.orig = orig;
	cam.camera_direction = vunit(camera_direction); // input에서 단위벡터를 검사해야함!
	fprintf(stderr, "D : ");
	vprint(vunit(cam.camera_direction));
	cam.viewport_h = 2 * tan(canvas->fov / 2) * focal_len;
	cam.viewport_w = cam.viewport_h * canvas->aspect_ratio; // canvas->aspect_ratio = w / h
	cam.focal_len = focal_len;
	fprintf(stderr, "viewport_h : %.4lf, viewport_w : %.4lf\n", cam.viewport_h, cam.viewport_w);
	fprintf(stderr, "focal_len : %.4lf\n", cam.focal_len);
	// cam.horizontal = vec3(cam.viewport_w, 0, 0);
	// horizontal = F(ront Vector, D) X Up(0, 1, 0)
	// camera_direction 과 Up vector 의 각이 
	//  0(0, 1, 0), PI(0, -1, 0) 일떄 sin 이 0이 되면서 수평방향이 영벡터가 됨(짐벌 락)
	//  0(0, 1, 0) : (1, 0, 0), PI(0, -1, 0) : (-1, 0, 0) 으로 수동 지정
	DcrossUP = vcross(cam.camera_direction, UP_VECTOR);
	// vprint(DcrossUP);
	if (vlength(DcrossUP) == 0)
	{
		if (check_eql_double(vangle(cam.camera_direction, UP_VECTOR), 0))
			DcrossUP = vec3(1, 0, 0);
		else
			DcrossUP = vec3(-1, 0, 0);
	}
	fprintf(stderr, "Dx : ");
	vprint(vunit(DcrossUP)); // Dx 방향
	cam.horizontal = vmult(vunit(DcrossUP), cam.viewport_w);

	// cam.vertical = vmult(UP_VECTOR, cam.viewport_h);
	// vertical = R X F(ront Vector, D)
	XcrossD = vcross(cam.horizontal, cam.camera_direction);
	// 서로 수직인 벡터 R과 F의 외적은 유일하게 존재
	fprintf(stderr, "Dy : ");
	vprint(vunit(XcrossD));
	cam.vertical = vmult(vunit(XcrossD), cam.viewport_h);
	// vprint(cam.vertical);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - D * focal_length
	cam.left_bottom = vminus(
						vminus(
							vminus(
								cam.orig, 
								vdivide(cam.horizontal, 2)),
			  				vdivide(cam.vertical, 2)), 
						vmult(cam.camera_direction, -focal_len));
	fprintf(stderr, "left_bottom : ");
	vprint((t_vec3)cam.left_bottom);
	return (cam);
}