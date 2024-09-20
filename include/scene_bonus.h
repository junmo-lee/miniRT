#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H

# include "structures_bonus.h"
# include "utils_bonus.h"
# include "mlx.h"


t_canvas	canvas(int width, int height, double h_fov);
t_camera	camera(t_canvas *canvas, t_point3 orig, t_point3 camera_direction);
t_sphere	*sphere(t_point3 center, double radius);
t_plain		*plain(t_point3 p, t_vec3 n);
t_cone		*cylinder(t_point3 center, t_vec3 n, double radius, double height);

t_object	*object(t_object_type type, void *element, t_attribute attrib);
t_light		*light_point(t_point3 light_origin, \
t_color3 light_color, double bright_ratio);

int			error_exit(t_vmlx *vmlx);
int			normal_exit(t_vmlx *vmlx);
int			key_press(int keycode, t_vmlx *vmlx);
int			make_window(t_vmlx	*vmlx);

t_scene		*parse_to_scene(t_parse *parsed);

t_color3	get_ambient(t_ambient_p *a_ptr);
void		get_camera(t_scene *scene, t_camera_p *c_ptr);
t_object	*get_light(t_light_p *l_ptr);
t_object	*get_world(t_object_p *o_ptr);

void		add_sphere(t_object *world, t_object_p *o_ptr);
void		add_plain(t_object *world, t_object_p *o_ptr);
void		add_cylinder(t_object *world, t_object_p *o_ptr);

// bonus
t_cone		*cone(t_point3 center, t_vec3 n, double radius, double height);
void		add_cone(t_object *world, t_object_p *o_ptr);

#endif