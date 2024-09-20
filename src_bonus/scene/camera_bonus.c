#include "scene_bonus.h"

// 두 벡터 사이의 길이(Rad), vec1 부터 vec2 까지
double	vangle(t_vec3 vec1, t_vec3 vec2)
{
	const double	len_vec1 = vlength(vec1);
	const double	len_vec2 = vlength(vec2);

	if (len_vec1 == 0 || len_vec2 == 0)
		return (0);
	else
		return (acos(vdot(vec1, vec2) / (len_vec1 * len_vec2)));
}

void	set_camera_pos(t_camera *cam)
{
	t_vec3			dcroosup;
	t_vec3			xcrossd;
	const t_vec3	up_vec = {0, 1, 0};
	t_vec3			bottom_frame;

	dcroosup = vcross(cam->camera_direction, up_vec);
	if (vlength(dcroosup) == 0)
	{
		if (check_eql_double(vangle(cam->camera_direction, up_vec), 0))
			dcroosup = vec3(1, 0, 0);
		else
			dcroosup = vec3(-1, 0, 0);
	}
	cam->dx = vunit(dcroosup);
	cam->horizontal = vscalar(cam->dx, cam->viewport_w);
	xcrossd = vcross(cam->horizontal, cam->camera_direction);
	cam->dy = vunit(xcrossd);
	cam->vertical = vscalar(cam->dy, cam->viewport_h);
	bottom_frame = vminus(vminus(cam->orig, vdivide(cam->horizontal, 2)), \
		vdivide(cam->vertical, 2));
	cam->left_bottom = vminus(bottom_frame, \
		vscalar(cam->camera_direction, -cam->focal_len));
}

t_camera	camera(t_canvas *canvas, t_point3 orig, t_point3 camera_direction)
{
	t_camera	cam;
	double		focal_len;

	ft_memset(&cam, 0, sizeof(cam));
	focal_len = 1.0;
	cam.orig = orig;
	cam.camera_direction = vunit(camera_direction);
	cam.viewport_w = 2.0 * tan(canvas->h_fov / 2) * focal_len;
	cam.viewport_h = cam.viewport_w / canvas->aspect_ratio;
	cam.focal_len = focal_len;
	set_camera_pos(&cam);
	return (cam);
}
