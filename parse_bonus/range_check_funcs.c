#include "parse_bonus.h"

void	check_color_range(t_parse *parsed_struct, char **splited_colors)
{
	if (splited_colors == NULL)
		parse_exit(parsed_struct);
	if (0 > ft_atof(splited_colors[0]) || ft_atof(splited_colors[0]) > 255)
		parse_exit(parsed_struct);
	else if (0 > ft_atof(splited_colors[1]) || ft_atof(splited_colors[1]) > 255)
		parse_exit(parsed_struct);
	else if (0 > ft_atof(splited_colors[2]) || ft_atof(splited_colors[2]) > 255)
		parse_exit(parsed_struct);
}

void	check_light_ratio_range(t_parse *parsed_struct, double num)
{
	if (num < 0 || num > 1)
		parse_exit(parsed_struct);
}

void	check_fov_range(t_parse *parsed_struct, double num)
{
	if (num < 0 || num > 180)
		parse_exit(parsed_struct);
}

void	check_normal_vector_range(t_parse *parsed_struct, char **splited_colors)
{
	if (splited_colors == NULL)
		parse_exit(parsed_struct);
	if (-1 > ft_atof(splited_colors[0]) || ft_atof(splited_colors[0]) > 1)
		parse_exit(parsed_struct);
	else if (-1 > ft_atof(splited_colors[1]) || ft_atof(splited_colors[1]) > 1)
		parse_exit(parsed_struct);
	else if (-1 > ft_atof(splited_colors[2]) || ft_atof(splited_colors[2]) > 1)
		parse_exit(parsed_struct);
	if (ft_atof(splited_colors[0]) == 0 && ft_atof(splited_colors[1]) == 0 \
	&& ft_atof(splited_colors[2]) == 0)
		parse_exit(parsed_struct);
}
