#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

# define WIN_NAME "miniRT"
# define R_WIDTH 600
# define R_HIGHT 600

# define SAMPLES_PER_PIXEL 1

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ray		t_ray;
typedef struct s_scene		t_scene;
typedef struct s_camera		t_camera;
typedef struct s_canvas		t_canvas;
typedef struct s_object		t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_plain		t_plain;
typedef struct s_cylinder	t_cylinder;
typedef struct s_cone		t_cone;
typedef struct s_light		t_light;
typedef struct s_hit_record	t_hit_record;
typedef struct s_object		t_object;
typedef int					t_bool;
typedef struct s_vmlx		t_vmlx;

# define FALSE 0
# define TRUE 1

typedef enum e_object_type
{
	NONE = 0,
	SP,
	PL,
	CY,
	CO,
	LIGHT_POINT
}	t_object_type;

typedef enum e_token_type
{
	COORDINATE = 1,
	NORMAL_VECTOR,
	COLOR
}	t_token_type;

# define EPSILON 1e-6 // 0.000001
# define LUMEN 1
# define DEFALUT_KSN 64 // shininess value, 물체의 반짝거리는 정도
# define KS 0.5 // [0,1] specular 강도, specular = spec ^ ksn

# define PLAIN_CHECKER_WIDTH 0.5
# define PLAIN_CHECKER_HEIGHT 0.5

# define CHECKER_TIMES 10

# define RGB_T 0
# define RGB_MAX 255.99

// mt19937
# define N 624
# define M 397
# define MATRIX_A 0x9908b0dfUL   /* constant vector a */
# define UPPER_MASK 0x80000000UL /* most significant w-r bits */
# define LOWER_MASK 0x7fffffffUL /* least significant r bits */

# define RAND_SEED 1234UL

typedef enum e_event
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	t_event;

typedef enum e_keycode
{
	KCODE_ESC = 53,
	KCODE_LEFT_ARROW = 123,
	KCODE_RIGHT_ARROW = 124,
	KCODE_DOWN_ARROW = 125,
	KCODE_UP_ARROW = 126
}	t_keycode;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ambient_p
{
	double	ratio;
	t_vec3	colors;
}	t_ambient_p;

typedef struct s_camera_p
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	int		fov;
}	t_camera_p;

typedef struct s_light_p
{
	t_vec3				coordinates;
	double				brightness;
	t_vec3				colors;
	struct s_light_p	*next_light;
}	t_light_p;

typedef struct s_sphere_p
{
	t_vec3	coordinates;
	double	diameter;
	t_vec3	colors;
	double	ksn;
	int		cd;
}	t_sphere_p;

typedef struct s_plane_p
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	t_vec3	colors;
	double	ksn;
	int		cd;
}	t_plane_p;

typedef struct s_cylinder_p
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	double	diameter;
	double	height;
	t_vec3	colors;
	double	ksn;
	int		cd;
}	t_cylinder_p;

typedef struct s_cone_p
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	double	diameter;
	double	height;
	t_vec3	colors;
	double	ksn;
	int		cd;
}	t_cone_p;

typedef struct s_object_p
{
	int					identifier;
	t_sphere_p			*sphere;
	t_plane_p			*plane;
	t_cylinder_p		*cylinder;
	t_cone_p			*cone;
	struct s_object_p	*next;
}	t_object_p;

typedef struct s_parse
{
	t_ambient_p		*ambient_pointer;
	t_camera_p		*camera_pointer;
	t_light_p		*light_pointer;
	t_object_p		*object_pointer;
}	t_parse;

typedef struct s_ambient
{
	double	ratio;
	t_vec3	colors;
}	t_ambient;

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}	t_ray;

typedef struct s_camera
{
	t_point3	orig;
	t_vec3		camera_direction;
	double		viewport_w;
	double		viewport_h;
	t_vec3		dx;
	t_vec3		dy;
	t_vec3		horizontal;
	t_vec3		vertical;
	double		focal_len;
	t_point3	left_bottom;
}	t_camera;

typedef struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
	double	h_fov;
	double	v_fov;
}	t_canvas;

typedef struct s_object
{
	t_object_type	type;
	void			*element;
	t_color3		albedo;
	double			ksn;
	int				cd;
	void			*next;
}	t_object;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
}	t_sphere;

typedef struct s_plain
{
	t_point3	p;
	t_vec3		n;
	t_vec3		vecu;
	t_vec3		vecv;
}	t_plain;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		n;
	double		radius;
	double		height;
	t_vec3		h;
	t_vec3		pc;
	double		pc_doc_hhat;
}	t_cylinder;
typedef struct s_cone
{
	t_point3	center;
	t_vec3		n;
	double		radius;
	double		height;
	t_vec3		h;
	t_point3	pointh;
	double		m;
	t_vec3		ph;
	double		ph_doc_hhat;
}	t_cone;

typedef struct s_light
{
	t_point3	origin;
	t_color3	light_color;
	double		bright_ratio;
}	t_light;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
	t_color3	albedo;
}	t_hit_record;

typedef struct s_eql
{
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		sqrtd;
	double		root1;
	double		root2;
}	t_eql;

typedef struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
}	t_scene;

typedef struct s_vmlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_scene	*scene;
}	t_vmlx;

typedef struct s_MT19937
{
	unsigned long	mt[N];
	int				mti;
}	t_MT19937;
typedef struct s_attribute
{
	t_color3	albedo;
	double		ksn;
	int			cd;
}	t_attribute;

#endif