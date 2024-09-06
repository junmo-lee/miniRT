#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "structures.h"

// create_funcs.c
void	*init_t_parse(t_parse *parse_struct);
t_ambient_p	*create_ambient_struct(t_parse *parsed_struct);
t_camera_p	*create_camera_struct(t_parse *parsed_strcut);
t_light_p		*create_light_struct(t_parse *parsed_struct);
t_object_p	*create_object_struct(t_parse *parsed_struct);
t_plane_p		*create_plane_struct(t_parse *parsed_struct);
t_sphere_p	*create_sphere_struct(t_parse *parsed_struct);
t_cylinder_p	*create_cylinder_struct(t_parse *parsed_struct);

//parse_functions.c
int		classify_identifier(t_parse *parsed_struct, char **strings);

// util_functions.c
void	print_strings(char **strings);
void	parse_exit(t_parse *parsed_struct);
void	splited_free(char **strings);
void	append_object_struct(t_parse *parsed_struct, t_object_p *object_struct);

// ft_atof.c
double	ft_atof(const char *str);

// parse.c
int		str_num_check(char *str);
int		strings_syntex_check(char **strings);
void	parse(t_parse *parsed_struct, char *file_location);

# endif