#include "../../include/parse.h"

t_cylinder_p	*create_cylinder_struct(t_parse *parsed_struct)
{
	t_cylinder_p	*cylinder_struct;

	cylinder_struct = (t_cylinder_p *)malloc(sizeof(t_cylinder_p));
	if (!cylinder_struct)
		parse_exit(parsed_struct, "Malloc error");
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

void	parse_cylinder(t_parse *parsed_struct, char **strings)
{
	t_cylinder_p	*cylinder;
	t_object_p		*object_struct;

	if (parsed_struct == NULL)
		parse_exit(parsed_struct, "parsed_struct is NULL");
	validate_tokens_cone_cylinder(parsed_struct, strings);
	cylinder = create_cylinder_struct(parsed_struct);
	assign_xyz_from_token(parsed_struct, \
	&cylinder->coordinates, strings[1], COORDINATE);
	assign_xyz_from_token(parsed_struct, \
	&cylinder->normal_vector, strings[2], NORMAL_VECTOR);
	cylinder->diameter = ft_atof(strings[3]);
	cylinder->height = ft_atof(strings[4]);
	assign_xyz_from_token(parsed_struct, &cylinder->colors, strings[5], COLOR);
	object_struct = create_object_struct(parsed_struct);
	object_struct->identifier = CY;
	object_struct->cylinder = cylinder;
	append_object_struct(parsed_struct, object_struct);
}
