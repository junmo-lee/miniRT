#include "../../include/parse_bonus.h"

t_plane_p	*create_plane_struct(t_parse *parsed_struct)
{
	t_plane_p		*plane_object;

	plane_object = (t_plane_p *)malloc(sizeof(t_plane_p));
	if (!plane_object)
		parse_exit(parsed_struct, "Malloc error");
	plane_object->coordinates.x = 0;
	plane_object->coordinates.y = 0;
	plane_object->coordinates.z = 0;
	plane_object->normal_vector.x = 0;
	plane_object->normal_vector.y = 0;
	plane_object->normal_vector.z = 0;
	plane_object->colors.x = 0;
	plane_object->colors.y = 0;
	plane_object->colors.z = 0;
	plane_object->ksn = 0;
	plane_object->cd = 0;
	return (plane_object);
}

void	validate_tokens_for_plane(t_parse *parsed_struct, char **strings)
{
	count_tokens_len(parsed_struct, strings, 6);
	validate_coordinate(parsed_struct, strings[1], 3);
	validate_coordinate(parsed_struct, strings[2], 3);
	validate_coordinate(parsed_struct, strings[3], 3);
	validate_coordinate(parsed_struct, strings[4], 1);
	validate_coordinate(parsed_struct, strings[5], 1);
}

void	parse_plane(t_parse *parsed_struct, char **strings)
{
	t_plane_p	*plane;
	t_object_p	*object_struct;

	if (parsed_struct == NULL)
		parse_exit(parsed_struct, "parsed_struct is NULL");
	validate_tokens_for_plane(parsed_struct, strings);
	plane = create_plane_struct(parsed_struct);
	assign_xyz_from_token(parsed_struct, \
	&plane->coordinates, strings[1], COORDINATE);
	assign_xyz_from_token(parsed_struct, \
	&plane->normal_vector, strings[2], NORMAL_VECTOR);
	assign_xyz_from_token(parsed_struct, &plane->colors, strings[3], COLOR);
	assign_ksn(parsed_struct, &plane->ksn, strings[4]);
	assign_cd(parsed_struct, &plane->cd, strings[5]);
	object_struct = create_object_struct(parsed_struct);
	object_struct->identifier = PL;
	object_struct->plane = plane;
	append_object_struct(parsed_struct, object_struct);
}
