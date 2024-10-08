#include "parse_bonus.h"

void	assign_xyz(t_parse *parsed_struct, \
t_vec3 *coordinate, char **xyz_tokens)
{
	if (xyz_tokens == NULL)
		parse_exit(parsed_struct, "Coordinate argument cannot be NULL");
	coordinate->x = ft_atof(xyz_tokens[0]);
	coordinate->y = ft_atof(xyz_tokens[1]);
	coordinate->z = ft_atof(xyz_tokens[2]);
}

void	parse_exit(t_parse *parsed_struct, char *err_mss)
{
	clean_parsed_struct(parsed_struct);
	printf("Error\n");
	printf("%s\n", err_mss);
	exit(1);
}

void	incorrect_name_exit(void)
{
	printf("Error\n");
	printf("Invalid file name\n");
	exit(1);
}

void	assign_xyz_from_token(t_parse *parsed_struct, \
t_vec3 *coordinate, char *str, int type)
{
	char	**xyz_tokens;

	xyz_tokens = ft_split(str, ',');
	if (type == NORMAL_VECTOR)
		check_normal_vector_range(parsed_struct, xyz_tokens);
	else if (type == COLOR)
		check_color_range(parsed_struct, xyz_tokens);
	assign_xyz(parsed_struct, coordinate, xyz_tokens);
	free_tokens(xyz_tokens);
}
