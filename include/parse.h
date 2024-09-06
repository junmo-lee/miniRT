#ifndef PARSE_H
# define PARSE_H

# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "structures.h"

# define DEFAULT 0
// # define SP 1
// # define PL	2
// # define CY 3
# define CR 4 //임시

typedef struct s_vec3 // 튜토리얼 것을 가져옴
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_ambient_p
{
	double	ratio;
	t_vec3	colors;
} t_ambient_p;

typedef struct s_camera_p
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	int		fov;
} t_camera_p;

typedef struct s_light_p
{
	t_vec3	coordinates;
	double	brightness;
	t_vec3	colors;
} t_light_p;

typedef struct s_sphere_p
{
	t_vec3	coordinates;
	double	diameter;
	t_vec3	colors;
} t_sphere_p;

typedef struct s_plane_p
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	t_vec3	colors;
} t_plane_p;

typedef struct s_cylinder_p
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	double	diameter;
	double	height;
	t_vec3	colors;
} t_cylinder_p;

typedef struct s_cone_p
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	double	diameter;
	double	height;
	t_vec3	colors;
} t_cone_p;


typedef	struct s_object_p
{
	int	identifier;
	t_sphere_p	*sphere;
	t_plane_p		*plane;
	t_cylinder_p	*cylinder;
	t_cone_p		*cone;
	struct s_object_p	*next;
}	t_object_p;

typedef struct s_parse
{
	t_ambient_p	*ambient_pointer;
	t_camera_p	*camera_pointer;
	t_light_p		*light_pointer;
	t_object_p	*object_pointer;
} t_parse;

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

# endif