#include "../../include/parse_bonus.h"

t_ambient_p	*create_ambient_struct(t_parse *parsed_struct)
{
	t_ambient_p	*ambient_struct;

	ambient_struct = (t_ambient_p *)malloc(sizeof(t_ambient_p));
	if (!ambient_struct)
		parse_exit(parsed_struct);
	ambient_struct->colors.x = 0;
	ambient_struct->colors.y = 0;
	ambient_struct->colors.z = 0;
	ambient_struct->ratio = 0;
	return (ambient_struct);
}

void	parse_ambient(t_parse *parsed_struct, char **tokens)
{
	t_ambient_p	*ambient;

	if (parsed_struct == NULL || parsed_struct->ambient_pointer != NULL)
		parse_exit(parsed_struct);
	count_tokens_len(parsed_struct, tokens, 3);
	validate_coordinate(parsed_struct, tokens[1], 1);
	validate_coordinate(parsed_struct, tokens[2], 3);
	ambient = create_ambient_struct(parsed_struct);
	ambient->ratio = ft_atof(tokens[1]);
	check_light_ratio_range(parsed_struct, ambient->ratio);
	assign_xyz_from_token(parsed_struct, &ambient->colors, tokens[2], COLOR);
	parsed_struct->ambient_pointer = ambient;
}
