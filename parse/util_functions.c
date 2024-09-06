#include "parse.h"

void	print_strings(char **strings)
{
	int	index;

	index = 0;
	while (strings[index] != NULL)
	{
		printf("%s ", strings[index]);
		index ++;
	}
}

void	free_object_list(t_object *object_struct)
{
	t_object	*current_node;
	t_object	*tem_node;

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
		free(parsed_struct->light_pointer);
	if (parsed_struct->object_pointer != NULL)
		free_object_list(parsed_struct->object_pointer);
}

void	parse_exit(t_parse *parsed_struct)
{
	clean_parsed_struct(parsed_struct);
	printf("parse_exit\n");
	exit(1);
}

void	splited_free(char **strings)
{
	int	index;

	index = 0;
	while (strings[index] != NULL)
	{
		free(strings[index]);
		index ++;
	}
	free(strings);
}

void	append_object_struct(t_parse *parsed_struct, t_object *object_struct)
{
	t_object *current_node;

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
