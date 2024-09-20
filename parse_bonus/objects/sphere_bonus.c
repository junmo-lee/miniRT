#include "../../include/parse_bonus.h"

t_sphere_p	*create_sphere_struct(t_parse *parsed_struct)
{
	t_sphere_p	*sphere_object;

	sphere_object = (t_sphere_p *)malloc(sizeof(t_sphere_p));
	if (!sphere_object)
		parse_exit(parsed_struct, "Malloc error");
	sphere_object->coordinates.x = 0;
	sphere_object->coordinates.y = 0;
	sphere_object->coordinates.z = 0;
	sphere_object->diameter = 0;
	sphere_object->colors.x = 0;
	sphere_object->colors.y = 0;
	sphere_object->colors.z = 0;
	sphere_object->ksn = 0;
	sphere_object->cd = 0;
	return (sphere_object);
}

void	validate_tokens_for_sphere(t_parse *parsed_struct, char **strings)
{
	count_tokens_len(parsed_struct, strings, 6);
	validate_coordinate(parsed_struct, strings[1], 3);
	validate_coordinate(parsed_struct, strings[2], 1);
	validate_coordinate(parsed_struct, strings[3], 3);
	validate_coordinate(parsed_struct, strings[4], 1);
	validate_coordinate(parsed_struct, strings[5], 1);
}

void	parse_sphere(t_parse *parsed_struct, char **strings)
{
	t_sphere_p	*sphere;
	t_object_p	*object_struct;

	if (parsed_struct == NULL)
		parse_exit(parsed_struct, "parsed_struct is NULL");
	validate_tokens_for_sphere(parsed_struct, strings);
	sphere = create_sphere_struct(parsed_struct);
	assign_xyz_from_token(parsed_struct, \
	&sphere->coordinates, strings[1], COORDINATE);
	sphere->diameter = ft_atof(strings[2]);
	assign_xyz_from_token(parsed_struct, &sphere->colors, strings[3], COLOR);
	assign_ksn(parsed_struct, &sphere->ksn, strings[4]);
	assign_cd(parsed_struct, &sphere->cd, strings[5]);
	object_struct = create_object_struct(parsed_struct);
	object_struct->identifier = SP;
	object_struct->sphere = sphere;
	append_object_struct(parsed_struct, object_struct);
}
