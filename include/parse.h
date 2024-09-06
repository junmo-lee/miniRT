#ifndef PARSE_H
# define PARSE_H

# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# define DEFAULT 0
# define SP 1
# define PL	2
# define CY 3
# define CR 4 //임시

typedef struct s_vec3 // 튜토리얼 것을 가져옴
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_ambient
{
	double	ratio;
	t_vec3	colors;
} t_ambient;

typedef struct s_camera
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	int		fov;
} t_camera;

typedef struct s_light
{
	t_vec3	coordinates;
	double	brightness;
	t_vec3	colors;
} t_light;

typedef struct s_sphere
{
	t_vec3	coordinates;
	double	diameter;
	t_vec3	colors;
} t_sphere;

typedef struct s_plane
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	t_vec3	colors;
} t_plane;

typedef struct s_cylinder
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	double	diameter;
	double	height;
	t_vec3	colors;
} t_cylinder;

typedef struct s_cone
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	double	diameter;
	double	height;
	t_vec3	colors;
} t_cone;


typedef	struct s_object
{
	int	identifier;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;
	struct s_object	*next;
}	t_object;

typedef struct s_parse
{
	t_ambient	*ambient_pointer;
	t_camera	*camera_pointer;
	t_light		*light_pointer;
	t_object	*object_pointer;
} t_parse;

// create_funcs.c
void	*init_t_parse(t_parse *parse_struct);
t_ambient	*create_ambient_struct(t_parse *parsed_struct);
t_camera	*create_camera_struct(t_parse *parsed_strcut);
t_light		*create_light_struct(t_parse *parsed_struct);
t_object	*create_object_struct(t_parse *parsed_struct);
t_plane		*create_plane_struct(t_parse *parsed_struct);
t_sphere	*create_sphere_struct(t_parse *parsed_struct);
t_cylinder	*create_cylinder_struct(t_parse *parsed_struct);

//parse_functions.c
int		classify_identifier(t_parse *parsed_struct, char **strings);

// util_functions.c
void	print_strings(char **strings);
void	parse_exit(t_parse *parsed_struct);
void	splited_free(char **strings);
void	append_object_struct(t_parse *parsed_struct, t_object *object_struct);

// ft_atof.c
double	ft_atof(const char *str);

# endif