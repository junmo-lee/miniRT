#include "../../include/parse_bonus.h"

t_camera_p	*create_camera_struct(t_parse *parsed_strcut)
{
	t_camera_p	*camera_struct;

	camera_struct = (t_camera_p *)malloc(sizeof(t_camera_p));
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

void	parse_camera(t_parse *parsed_struct, char **strings)
{
	t_camera_p	*camera;

	if (parsed_struct == NULL || parsed_struct->camera_pointer != NULL)
		parse_exit(parsed_struct);
	count_tokens_len(parsed_struct, strings, 4);
	validate_coordinate(parsed_struct, strings[1], 3);
	validate_coordinate(parsed_struct, strings[2], 3);
	validate_coordinate(parsed_struct, strings[3], 1);
	camera = create_camera_struct(parsed_struct);
	assign_xyz_from_token(parsed_struct, \
	&camera->coordinates, strings[1], COORDINATE);
	assign_xyz_from_token(parsed_struct, \
	&camera->normal_vector, strings[2], NORMAL_VECTOR);
	camera->fov = ft_atof(strings[3]);
	check_fov_range(parsed_struct, camera->fov);
	parsed_struct->camera_pointer = camera;
}
