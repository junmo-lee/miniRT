#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "structures.h"

// parser.c
void		parse(t_parse *parsed_struct, char *file_location);

// check_functions.c
void		count_tokens_len(t_parse *parsed_struct, char **strings, int num);
void		validate_coordinate(t_parse *parsed_struct, char *str, int num);
int			check_numeric(char *str);
int			check_all_numeric(char **strings);

// range_check_funcs.c
void		check_color_range(t_parse *parsed_struct, char **splited_colors);
void		check_light_ratio_range(t_parse *parsed_struct, double num);
void		check_normal_vector_range(t_parse *parsed_struct, char **splited_colors);
void		check_fov_range(t_parse *parsed_struct, double num);

// object_dir
void		parse_ambient(t_parse *parsed_struct, char **strings);
void		parse_camera(t_parse *parsed_struct, char **strings);
void		parse_light(t_parse *parsed_struct, char **strings);
void		parse_plane(t_parse *parsed_struct, char **strings);
void		parse_sphere(t_parse *parsed_struct, char **strings);
void		parse_cylinder(t_parse *parsed_struct, char **strings);
void		parse_cone(t_parse *parsed_struct, char **strings);

//parse_functions.c
void		assign_xyz(t_parse *parsed_struct, t_vec3 *coordinate, char **splited_colors);
void		assign_xyz_from_token(t_parse *parsed_struct, t_vec3 *coordinate, char *str, int type);
void		parse_exit(t_parse *parsed_struct);

// util_functions.c
void		free_tokens(char **strings);
void		append_object_struct(t_parse *parsed_struct, t_object_p *object_struct);
void		clean_parsed_struct(t_parse *parsed_struct);
t_object_p	*create_object_struct(t_parse *parsed_struct);

// ft_atof.c
double		ft_atof(const char *str);

# endif