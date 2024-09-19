#include "../include/parse_bonus.h"

void	*init_parse_struct(t_parse *parse_struct)
{
	parse_struct->ambient_pointer = NULL;
	parse_struct->camera_pointer = NULL;
	parse_struct->light_pointer = NULL;
	parse_struct->object_pointer = NULL;
	return (parse_struct);
}

int	classify_identifier(t_parse *parsed_struct, char **strings)
{
	int	index;

	index = 0;
	while (strings[index] != NULL)
	{
		if (ft_strncmp(strings[index], "A", 2) == 0)
			parse_ambient(parsed_struct, strings);
		else if (ft_strncmp(strings[index], "C", 2) == 0)
			parse_camera(parsed_struct, strings);
		else if (ft_strncmp(strings[index], "L", 2) == 0)
			parse_light(parsed_struct, strings);
		else if (ft_strncmp(strings[index], "pl", 3) == 0)
			parse_plane(parsed_struct, strings);
		else if (ft_strncmp(strings[index], "sp", 3) == 0)
			parse_sphere(parsed_struct, strings);
		else if (ft_strncmp(strings[index], "cy", 3) == 0)
			parse_cylinder(parsed_struct, strings);
		else if (ft_strncmp(strings[index], "co", 3) == 0)
			parse_cone(parsed_struct, strings);
		index ++;
	}
	return (0);
}

void	parse(t_parse *parsed_struct, char *file_location)
{
	int			fd;
	char		*buf;
	char		**tokens;

	buf = NULL;
	init_parse_struct(parsed_struct);
	fd = open(file_location, O_RDONLY);
	if (fd == -1)
		parse_exit(parsed_struct);
	while (1)
	{
		buf = get_next_line(fd);
		if (buf == NULL)
			break ;
		tokens = ft_split(buf, ' ');
		if (check_all_numeric(tokens) == -1)
		{
			free(buf);
			free_tokens(tokens);
			continue ;
		}
		classify_identifier(parsed_struct, tokens);
		free_tokens(tokens);
		free(buf);
	}
}
