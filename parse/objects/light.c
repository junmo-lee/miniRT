#include "../../include/parse.h"

t_light_p	*create_light_struct(t_parse *parsed_struct)
{
	t_light_p	*light_struct;

	light_struct = (t_light_p *)malloc(sizeof(t_light_p));
	if (!light_struct)
		parse_exit(parsed_struct, "Malloc error");
	light_struct->coordinates.x = 0;
	light_struct->coordinates.y = 0;
	light_struct->coordinates.z = 0;
	light_struct->brightness = 0;
	light_struct->colors.x = 0;
	light_struct->colors.y = 0;
	light_struct->colors.z = 0;
	light_struct->next_light = NULL;
	return (light_struct);
}

void	append_light_struct(t_parse *parsed_struct, t_light_p *new_node)
{
	t_light_p	*current_node;

	if (parsed_struct == NULL || new_node == NULL)
		parse_exit(parsed_struct, "parsed_struct is NULL");
	if (parsed_struct->light_pointer == NULL)
		parsed_struct->light_pointer = new_node;
	else
	{
		current_node = parsed_struct->light_pointer;
		while (current_node->next_light != NULL)
			current_node = current_node->next_light;
		current_node->next_light = new_node;
	}
}

void	free_light_list(t_light_p *light_struct)
{
	t_light_p	*current_node;
	t_light_p	*tem_node;

	current_node = light_struct;
	while (current_node != NULL)
	{
		tem_node = current_node;
		current_node = current_node->next_light;
		free(tem_node);
	}
}

void	parse_light(t_parse *parsed_struct, char **strings)
{
	t_light_p	*light;

	if (parsed_struct == NULL)
		parse_exit(parsed_struct, "parsed_struct is NULL");
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
	append_light_struct(parsed_struct, light);
}
