#include "../../include/parse.h"

t_light_p	*create_light_struct(t_parse *parsed_struct)
{
	t_light_p	*light_struct;

	light_struct = (t_light_p *)malloc(sizeof(t_light_p));
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

void	parse_light(t_parse *parsed_struct, char **strings)
{
	t_light_p	*light;

	if (parsed_struct == NULL || parsed_struct->light_pointer != NULL)
		parse_exit(parsed_struct);
	count_tokens_len(parsed_struct, strings, 4);
	validate_coordinate(parsed_struct, strings[1], 3);
	validate_coordinate(parsed_struct, strings[2], 1);
	validate_coordinate(parsed_struct, strings[3], 3);
	light = create_light_struct(parsed_struct);
	assign_xyz_from_token(parsed_struct, \
	&light->coordinates, strings[1], COORDINATE);
	light->brightness = ft_atof(strings[2]);
	check_light_ratio_range(parsed_struct, light->brightness);
	assign_xyz_from_token(parsed_struct, &light->colors, strings[3], COLOR);
	parsed_struct->light_pointer = light;
}
