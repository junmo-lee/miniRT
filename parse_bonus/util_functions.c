#include "parse_bonus.h"

void	free_object_list(t_object_p *object_struct)
{
	t_object_p	*current_node;
	t_object_p	*tem_node;

	current_node = object_struct;
	while (current_node != NULL)
	{
		tem_node = current_node;
		current_node = current_node->next;
		if (tem_node->sphere != NULL)
			free(tem_node->sphere);
		else if (tem_node->plane != NULL)
			free(tem_node->plane);
		else if (tem_node->cylinder != NULL)
			free(tem_node->cylinder);
		else if (tem_node->cone != NULL)
			free(tem_node->cone);
		free(tem_node);
	}
}

void	clean_parsed_struct(t_parse *parsed_struct)
{
	if (parsed_struct == NULL)
		return ;
	if (parsed_struct->ambient_pointer != NULL)
		free(parsed_struct->ambient_pointer);
	if (parsed_struct->camera_pointer != NULL)
		free(parsed_struct->camera_pointer);
	if (parsed_struct->light_pointer != NULL)
		free_light_list(parsed_struct->light_pointer);
	if (parsed_struct->object_pointer != NULL)
		free_object_list(parsed_struct->object_pointer);
}

void	free_tokens(char **strings)
{
	int	index;

	index = 0;
	while (strings[index] != NULL)
	{
		free(strings[index]);
		strings[index] = NULL;
		index ++;
	}
	free(strings);
	strings = NULL;
}

t_object_p	*create_object_struct(t_parse *parsed_struct)
{
	t_object_p	*object_struct;

	object_struct = (t_object_p *)malloc(sizeof(t_object_p));
	if (!object_struct)
		parse_exit(parsed_struct);
	object_struct->identifier = NONE;
	object_struct->cylinder = NULL;
	object_struct->plane = NULL;
	object_struct->sphere = NULL;
	object_struct->cone = NULL;
	object_struct->next = NULL;
	return (object_struct);
}

void	append_object_struct(t_parse *parsed_struct, t_object_p *object_struct)
{
	t_object_p	*current_node;

	if (parsed_struct == NULL || object_struct == NULL)
		parse_exit(parsed_struct);
	if (parsed_struct->object_pointer == NULL)
		parsed_struct->object_pointer = object_struct;
	else
	{
		current_node = parsed_struct->object_pointer;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = object_struct;
	}
}
