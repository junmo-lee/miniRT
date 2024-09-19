#include "../../include/parse_bonus.h"

t_cone_p	*create_cone_struct(t_parse *parsed_struct)
{
	t_cone_p	*cone_struct;

	cone_struct = (t_cone_p *)malloc(sizeof(t_cone_p));
	if (!cone_struct)
		parse_exit(parsed_struct);
	cone_struct->coordinates.x = 0;
	cone_struct->coordinates.y = 0;
	cone_struct->coordinates.z = 0;
	cone_struct->normal_vector.x = 0;
	cone_struct->normal_vector.y = 0;
	cone_struct->normal_vector.z = 0;
	cone_struct->diameter = 0;
	cone_struct->height = 0;
	cone_struct->colors.x = 0;
	cone_struct->colors.y = 0;
	cone_struct->colors.z = 0;
	cone_struct->ksn = 0;
	cone_struct->cd = 0;
	return (cone_struct);
}

void	validate_tokens_cone_cylinder(t_parse *parsed_struct, char **strings)
{
	count_tokens_len(parsed_struct, strings, 8);
	validate_coordinate(parsed_struct, strings[1], 3);
	validate_coordinate(parsed_struct, strings[2], 3);
	validate_coordinate(parsed_struct, strings[3], 1);
	validate_coordinate(parsed_struct, strings[4], 1);
	validate_coordinate(parsed_struct, strings[5], 3);
	validate_coordinate(parsed_struct, strings[6], 1);
	validate_coordinate(parsed_struct, strings[7], 1);
}

void	parse_cone(t_parse *parsed_struct, char **strings)
{
	t_cone_p		*cone;
	t_object_p		*object_struct;

	if (parsed_struct == NULL)
		parse_exit(parsed_struct);
	validate_tokens_cone_cylinder(parsed_struct, strings);
	cone = create_cone_struct(parsed_struct);
	assign_xyz_from_token(parsed_struct, \
	&cone->coordinates, strings[1], COORDINATE);
	assign_xyz_from_token(parsed_struct, \
	&cone->normal_vector, strings[2], NORMAL_VECTOR);
	cone->diameter = ft_atof(strings[3]);
	cone->height = ft_atof(strings[4]);
	assign_xyz_from_token(parsed_struct, &cone->colors, strings[5], COLOR);
	assign_ksn(parsed_struct, &cone->ksn, strings[6]);
	assign_cd(parsed_struct, &cone->cd, strings[7]);
	object_struct = create_object_struct(parsed_struct);
	object_struct->identifier = CO;
	object_struct->cone = cone;
	append_object_struct(parsed_struct, object_struct);
}
