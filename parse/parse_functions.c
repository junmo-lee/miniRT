#include "parse.h"

void	color_range_check(t_parse *parsed_struct, char **splited_colors)
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

void	put_colors(t_parse *parsed_struct, t_ambient **ambient_struct, char **splited_colors)
{
	if (splited_colors == NULL)
		parse_exit(parsed_struct);
	(*ambient_struct)->colors.x = ft_atof(splited_colors[0]);
	(*ambient_struct)->colors.y = ft_atof(splited_colors[1]);
	(*ambient_struct)->colors.z = ft_atof(splited_colors[2]);
}

void	put_coordinate_camera_struct(t_parse *parsed_struct, t_camera **camera_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*camera_struct)->coordinates.x = ft_atof(splited_xyz[0]);
	(*camera_struct)->coordinates.y = ft_atof(splited_xyz[1]);
	(*camera_struct)->coordinates.z = ft_atof(splited_xyz[2]);
}

void	put_vector_camera_struct(t_parse *parsed_struct, t_camera **camera_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*camera_struct)->normal_vector.x = ft_atof(splited_xyz[0]);
	(*camera_struct)->normal_vector.y = ft_atof(splited_xyz[1]);
	(*camera_struct)->normal_vector.z = ft_atof(splited_xyz[2]);
}

void	count_strings_len(t_parse *parsed_struct, char **strings, int num)
{
	int index;

	index = 0;
	while (strings[index] != NULL)
	{
		// printf("%d ", strings[index]);
		index ++;
	}
	// printf("\n");
	if (num != index)
		parse_exit(parsed_struct);
}

void	coordinate_check(t_parse *parsed_struct, char *str, int num)
{
	char	**splited_xyz;

	if (str == NULL)
		parse_exit(parsed_struct);
	splited_xyz = ft_split(str, ',');
	count_strings_len(parsed_struct, splited_xyz, num);
}

void	parse_ambient(t_parse *parsed_struct, char **strings)
{
	t_ambient	*ambient_struct;
	char		**splited_colors;

	if (parsed_struct == NULL || parsed_struct->ambient_pointer != NULL) //ambient_struct가 있으면 추가하면 안 됨 에러.
		parse_exit(parsed_struct);
	count_strings_len(parsed_struct, strings, 3); // 총 strings의 문자수가 몇 개 인지 체크
	coordinate_check(parsed_struct, strings[1], 1); // ratio 갯수 확인
	coordinate_check(parsed_struct, strings[2], 3); // colors 갯수 확인
	ambient_struct = create_ambient_struct(parsed_struct);
	ambient_struct->ratio = ft_atof(strings[1]); //-- 두개 나오는 것은 push swap에 것을 가져오면 될듯. **빛 범위 0~1인거 확인 하는 코드 없음 넣어야됨
	splited_colors = ft_split(strings[2], ','); // 스플릿 한거 free 해줘야 함.
	color_range_check(parsed_struct, splited_colors); // 아마 그냥 parse_exit이면 ambient_struct가 릭이 날 것 같은데, 그것은 나중에 해결
	put_colors(parsed_struct, &ambient_struct, splited_colors);
	parsed_struct->ambient_pointer = ambient_struct; // parse_exit 걸때 parsed_struct free 해주는 것 말고도 ambient_struct이 연결되기 전이니까 따로 free 해줘야 됨
	splited_free(splited_colors);
}

void	parse_camera(t_parse *parsed_struct, char **strings)
{
	t_camera	*camera_struct;
	char		**splited_xyz;

	if (parsed_struct == NULL || parsed_struct->camera_pointer != NULL)
		parse_exit(parsed_struct);
	count_strings_len(parsed_struct, strings, 4);
	coordinate_check(parsed_struct, strings[1], 3);
	coordinate_check(parsed_struct, strings[2], 3);
	coordinate_check(parsed_struct, strings[3], 1);
	camera_struct = create_camera_struct(parsed_struct);
	splited_xyz = ft_split(strings[1], ',');
	put_coordinate_camera_struct(parsed_struct, &camera_struct, splited_xyz);
	splited_free(splited_xyz); // 스플릿 한거 free 해주는 함수
	splited_xyz = ft_split(strings[2], ',');
	put_vector_camera_struct(parsed_struct, &camera_struct, splited_xyz);
	splited_free(splited_xyz);
	camera_struct->fov = ft_atof(strings[3]); // fov 값을 0~180 정도로 체크하는 함수가 필요
	parsed_struct->camera_pointer = camera_struct;
}

void	put_coordinate_light_struct(t_parse *parsed_struct, t_light **light_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*light_struct)->coordinates.x = ft_atof(splited_xyz[0]);
	(*light_struct)->coordinates.y = ft_atof(splited_xyz[1]);
	(*light_struct)->coordinates.z = ft_atof(splited_xyz[2]);
}

void	put_colors_light_struct(t_parse *parsed_struct, t_light **light_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*light_struct)->colors.x = ft_atof(splited_xyz[0]);
	(*light_struct)->colors.y = ft_atof(splited_xyz[1]);
	(*light_struct)->colors.z = ft_atof(splited_xyz[2]);
}

void	parse_light(t_parse *parsed_struct, char **strings)
{
	t_light *light_struct;
	char 	**splited_xyz;

	if (parsed_struct == NULL || parsed_struct->light_pointer != NULL)
		parse_exit(parsed_struct);
	count_strings_len(parsed_struct, strings, 4);
	coordinate_check(parsed_struct, strings[1], 3);
	coordinate_check(parsed_struct, strings[2], 1);
	coordinate_check(parsed_struct, strings[3], 3);
	light_struct = create_light_struct(parsed_struct);
	splited_xyz = ft_split(strings[1], ',');
	put_coordinate_light_struct(parsed_struct, &light_struct, splited_xyz);
	splited_free(splited_xyz);
	light_struct->brightness = ft_atof(strings[2]); // 밝기 범위 잇어야 됨
	splited_xyz = ft_split(strings[3], ',');
	put_colors_light_struct(parsed_struct, &light_struct, splited_xyz);
	splited_free(splited_xyz);
	parsed_struct->light_pointer = light_struct;
}

void	put_coordinate_plane_struct(t_parse *parsed_struct, t_plane **plane_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*plane_struct)->coordinates.x = ft_atof(splited_xyz[0]);
	(*plane_struct)->coordinates.y = ft_atof(splited_xyz[1]);
	(*plane_struct)->coordinates.z = ft_atof(splited_xyz[2]);
}

void	put_normal_vector_plane(t_parse *parsed_struct, t_plane **plane_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*plane_struct)->normal_vector.x = ft_atof(splited_xyz[0]);
	(*plane_struct)->normal_vector.y = ft_atof(splited_xyz[1]);
	(*plane_struct)->normal_vector.z = ft_atof(splited_xyz[2]);
}

void	put_colors_plane_struct(t_parse *parsed_struct, t_plane **plane_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*plane_struct)->colors.x = ft_atof(splited_xyz[0]);
	(*plane_struct)->colors.y = ft_atof(splited_xyz[1]);
	(*plane_struct)->colors.z = ft_atof(splited_xyz[2]);
}

void	parse_plane(t_parse *parsed_struct, char **strings)
{
	t_plane		*plane_struct;
	t_object	*object_struct;
	char		**splited_xyz;

	if (parsed_struct == NULL)
		parse_exit(parsed_struct);
	count_strings_len(parsed_struct, strings, 4);
	coordinate_check(parsed_struct, strings[1], 3);
	coordinate_check(parsed_struct, strings[2], 3);
	coordinate_check(parsed_struct, strings[3], 3);
	plane_struct = create_plane_struct(parsed_struct);
	splited_xyz = ft_split(strings[1], ',');
	put_coordinate_plane_struct(parsed_struct, &plane_struct, splited_xyz);
	splited_free(splited_xyz);
	splited_xyz = ft_split(strings[2], ',');
	put_normal_vector_plane(parsed_struct, &plane_struct, splited_xyz);
	splited_free(splited_xyz);
	splited_xyz = ft_split(strings[3], ',');
	put_colors_plane_struct(parsed_struct, &plane_struct, splited_xyz);
	splited_free(splited_xyz);
	object_struct = create_object_struct(parsed_struct);
	object_struct->identifier = PL;
	object_struct->plane = plane_struct;
	append_object_struct(parsed_struct, object_struct);
}

void	put_coordinate_sphere_struct(t_parse *parsed_struct, t_sphere **sphere_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*sphere_struct)->coordinates.x = ft_atof(splited_xyz[0]);
	(*sphere_struct)->coordinates.y = ft_atof(splited_xyz[1]);
	(*sphere_struct)->coordinates.z = ft_atof(splited_xyz[2]);
}

void	put_colors_sphere_struct(t_parse *parsed_struct, t_sphere **sphere_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*sphere_struct)->colors.x = ft_atof(splited_xyz[0]);
	(*sphere_struct)->colors.y = ft_atof(splited_xyz[1]);
	(*sphere_struct)->colors.z = ft_atof(splited_xyz[2]);
}

void	parse_sphere(t_parse *parsed_struct, char **strings)
{
	t_sphere	*sphere_struct;
	t_object	*object_struct;
	char		**splited_xyz;

	if (parsed_struct == NULL)
		parse_exit(parsed_struct);
	count_strings_len(parsed_struct, strings, 4);
	coordinate_check(parsed_struct, strings[1], 3);
	coordinate_check(parsed_struct, strings[2], 1);
	coordinate_check(parsed_struct, strings[3], 3);
	sphere_struct = create_sphere_struct(parsed_struct);
	splited_xyz = ft_split(strings[1], ',');
	put_coordinate_sphere_struct(parsed_struct, &sphere_struct, splited_xyz);
	splited_free(splited_xyz);
	sphere_struct->diameter = ft_atof(strings[2]);
	splited_xyz = ft_split(strings[3], ',');
	put_colors_sphere_struct(parsed_struct, &sphere_struct, splited_xyz);
	splited_free(splited_xyz);
	object_struct = create_object_struct(parsed_struct);
	object_struct->identifier = SP;
	object_struct->sphere = sphere_struct;
	append_object_struct(parsed_struct, object_struct);
}

void	put_coordinate_cylinder_struct(t_parse *parsed_struct, t_cylinder **cylinder_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*cylinder_struct)->coordinates.x = ft_atof(splited_xyz[0]);
	(*cylinder_struct)->coordinates.y = ft_atof(splited_xyz[1]);
	(*cylinder_struct)->coordinates.z = ft_atof(splited_xyz[2]);
}

void	put_normal_cylinder_struct(t_parse *parsed_struct, t_cylinder **cylinder_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*cylinder_struct)->normal_vector.x = ft_atof(splited_xyz[0]);
	(*cylinder_struct)->normal_vector.y = ft_atof(splited_xyz[1]);
	(*cylinder_struct)->normal_vector.z = ft_atof(splited_xyz[2]);
}

void	put_colors_cylinder_struct(t_parse *parsed_struct, t_cylinder **cylinder_struct, char **splited_xyz)
{
	if (splited_xyz == NULL)
		parse_exit(parsed_struct);
	(*cylinder_struct)->colors.x = ft_atof(splited_xyz[0]);
	(*cylinder_struct)->colors.y = ft_atof(splited_xyz[1]);
	(*cylinder_struct)->colors.z = ft_atof(splited_xyz[2]);
}

void	parse_cylinder(t_parse *parsed_struct, char **strings)
{
	t_cylinder	*cylinder_struct;
	t_object	*object_struct;
	char		**splited_xyz;

	if (parsed_struct == NULL)
		parse_exit(parsed_struct);
	count_strings_len(parsed_struct, strings, 6);
	coordinate_check(parsed_struct, strings[1], 3);
	coordinate_check(parsed_struct, strings[2], 3);
	coordinate_check(parsed_struct, strings[3], 1);
	coordinate_check(parsed_struct, strings[4], 1);
	coordinate_check(parsed_struct, strings[5], 3);
	cylinder_struct = create_cylinder_struct(parsed_struct);

	splited_xyz = ft_split(strings[1], ',');
	put_coordinate_cylinder_struct(parsed_struct, &cylinder_struct, splited_xyz);
	splited_free(splited_xyz);

	splited_xyz = ft_split(strings[2], ',');
	put_normal_cylinder_struct(parsed_struct, &cylinder_struct, splited_xyz);
	splited_free(splited_xyz);

	cylinder_struct->diameter = ft_atof(strings[3]);
	cylinder_struct->height = ft_atof(strings[4]);

	splited_xyz = ft_split(strings[5], ',');
	put_colors_cylinder_struct(parsed_struct, &cylinder_struct, splited_xyz);
	splited_free(splited_xyz);

	object_struct = create_object_struct(parsed_struct);
	object_struct->identifier = CY;
	object_struct->cylinder = cylinder_struct;
	append_object_struct(parsed_struct, object_struct);
}

int	classify_identifier(t_parse *parsed_struct, char **strings)
{
	int	index;

	index = 0;
	while (strings[index] != NULL)
	{
		if (ft_strncmp(strings[index], "A", 2) == 0) // 처음 문자열만 분류 되도록 만들까? , 각각의 split한 문자열들이 갯수가 맞는 지 확인 해야할듯. 짤려 있으면 세그 뜰 수 도. 세그 뜸, 좌표들은 좌표인지 확인하는 과정이 있어야 할듯. 컴마로 스플릿 해서 몇개로 나눠지는 지로 판단해도 좋을듯.
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
		index ++;
	}
	return (0);
}