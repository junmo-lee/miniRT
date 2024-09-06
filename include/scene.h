#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"
# include "mlx.h"

t_canvas    canvas(int  width, int height, double h_fov);
t_camera    camera(t_canvas *canvas, t_point3 orig, t_point3 camera_direction);
t_sphere    *sphere(t_point3 center, double radius);
t_plain		*plain(t_point3 P, t_vec3 n);
t_cone		*cylinder(t_point3 center, t_vec3 n, double radius, double height);

// bonus
t_cone		*cone(t_point3 center, t_vec3 n, double radius, double height);

t_object    *object(t_object_type type, void *element, t_color3 albedo);
t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio);

t_scene 	*scene_init(void);

int	error_exit(t_vmlx *vmlx);
int	normal_exit(t_vmlx *vmlx);
int	key_press(int keycode, t_vmlx *vmlx);
int	make_window(t_vmlx	*vmlx);

t_scene *parse_to_scene(t_parse* parsed);

#endif