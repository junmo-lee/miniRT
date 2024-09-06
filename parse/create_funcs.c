# include "parse.h"

void	*init_t_parse(t_parse *parse_struct)
{
	parse_struct->ambient_pointer = NULL;
	parse_struct->camera_pointer = NULL;
	parse_struct->light_pointer = NULL;
	parse_struct->object_pointer = NULL;
	return (parse_struct);
}

t_ambient	*create_ambient_struct(t_parse *parsed_struct)
{
	t_ambient	*ambient_struct;

	ambient_struct = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ambient_struct)
		parse_exit(parsed_struct);
	ambient_struct->colors.x = 0;
	ambient_struct->colors.y = 0;
	ambient_struct->colors.z = 0;
	ambient_struct->ratio = 0;
	return (ambient_struct);
}

t_camera	*create_camera_struct(t_parse *parsed_strcut)
{
	t_camera	*camera_struct;

	camera_struct = (t_camera *)malloc(sizeof(t_camera));
	if (!camera_struct)
		parse_exit(parsed_strcut);
	camera_struct->coordinates.x = 0;
	camera_struct->coordinates.y = 0;
	camera_struct->coordinates.z = 0;
	camera_struct->normal_vector.x = 0;
	camera_struct->normal_vector.y = 0;
	camera_struct->normal_vector.z = 0;
	camera_struct->fov = 0;
	return (camera_struct);
}

t_light	*create_light_struct(t_parse *parsed_struct)
{
	t_light	*light_struct;

	light_struct = (t_light *)malloc(sizeof(t_light));
	if (!light_struct)
		parse_exit(parsed_struct);
	light_struct->coordinates.x = 0;
	light_struct->coordinates.y = 0;
	light_struct->coordinates.z = 0;
	light_struct->brightness = 0;
	light_struct->colors.x = 0;
	light_struct->colors.y = 0;
	light_struct->colors.z = 0;
	return (light_struct);
}

t_object	*create_object_struct(t_parse *parsed_struct)
{
	t_object	*object_struct;

	object_struct = (t_object *)malloc(sizeof(t_object));
	if (!object_struct)
		parse_exit(parsed_struct);
	object_struct->identifier = DEFAULT;
	object_struct->cylinder = NULL;
	object_struct->plane = NULL;
	object_struct->sphere = NULL;
	object_struct->cone = NULL;
	object_struct->next = NULL;
	return (object_struct);
}

t_plane		*create_plane_struct(t_parse *parsed_struct)
{
	t_plane		*plane_object;

	plane_object = (t_plane *)malloc(sizeof(t_plane));
	if (!plane_object)
		parse_exit(parsed_struct);
	plane_object->coordinates.x = 0;
	plane_object->coordinates.y = 0;
	plane_object->coordinates.z = 0;
	plane_object->normal_vector.x = 0;
	plane_object->normal_vector.y = 0;
	plane_object->normal_vector.z = 0;
	plane_object->colors.x = 0;
	plane_object->colors.y = 0;
	plane_object->colors.z = 0;
	return (plane_object);
}

t_sphere	*create_sphere_struct(t_parse *parsed_struct)
{
	t_sphere	*sphere_object;

	sphere_object = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere_object)
		parse_exit(parsed_struct);
	sphere_object->coordinates.x = 0;
	sphere_object->coordinates.y = 0;
	sphere_object->coordinates.z = 0;
	sphere_object->diameter = 0;
	sphere_object->colors.x = 0;
	sphere_object->colors.y = 0;
	sphere_object->colors.z = 0;
	return (sphere_object);
}

t_cylinder	*create_cylinder_struct(t_parse *parsed_struct)
{
	t_cylinder	*cylinder_struct;

	cylinder_struct = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder_struct)
		parse_exit(parsed_struct);
	cylinder_struct->coordinates.x = 0;
	cylinder_struct->coordinates.y = 0;
	cylinder_struct->coordinates.z = 0;
	cylinder_struct->normal_vector.x = 0;
	cylinder_struct->normal_vector.y = 0;
	cylinder_struct->normal_vector.z = 0;
	cylinder_struct->diameter = 0;
	cylinder_struct->height = 0;
	cylinder_struct->colors.x = 0;
	cylinder_struct->colors.y = 0;
	cylinder_struct->colors.z = 0;
	return (cylinder_struct);
}
