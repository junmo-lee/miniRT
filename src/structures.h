#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;

typedef struct s_scene t_scene;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;

typedef struct s_object t_object;
typedef struct s_sphere t_sphere;
typedef struct s_light  t_light;
typedef int             t_bool;

typedef struct s_hit_record t_hit_record;
typedef struct  s_object    t_object;

# define FALSE 0
# define TRUE 1

// enum 으로 바꾸어도 될듯
typedef int             t_object_type;
# define SP 0
# define LIGHT_POINT 1

# define EPSILON 1e-6 // 0.000001
# define LUMEN 3
// # define PI 3.14159265358979323846

// 예제 케이스와 유사한 값으로
# define R_WIDTH 600
# define R_HIGHT 300

// 예제에서는 (1, 0, 0) 이 수평방향(오른쪽) 이 되도록, D = (0, Dy, -1) 꼴이어야 함  
# define EXAMPLE_DX 0
# define EXAMPLE_DY 0 // Dy
# define EXAMPLE_DZ -1
# define EXAMPLE_FOV 90

# define SAMPLES_PER_PIXEL 4

struct s_vec3
{
	double x;
	double y;
	double z;
};

struct  s_ray
{
	t_point3    orig;
	t_vec3      dir;
};

struct  s_camera
{
	t_point3    orig;  // 카메라 원점(위치)
	t_vec3		camera_direction; // 카메라 방향(벡터)
	double      viewport_w; // 뷰포트 가로길이
	double      viewport_h; // 뷰포트 세로길이
	t_vec3		dx; // 수평(x) 단위벡터 horizontal / viewport_w
	t_vec3		dy; // 수직(y) 단위벡터 vertical / viewport_h
	t_vec3      horizontal; // 수평길이 벡터
	t_vec3      vertical; // 수직길이 벡터
	double      focal_len; // focal length
	t_point3    left_bottom; // 왼쪽 아래 코너점
};

struct  s_canvas
{
	int     width; //canvas width
	int     height; //canvas height;
	double  aspect_ratio; //종횡비
	double	fov; // to radian
};

struct	s_object
{
    t_object_type   type;
    void            *element;
	t_color3        albedo;
    void            *next;
};

struct  s_sphere
{
	t_point3    center;
	double      radius;
	double      radius2;
};

struct      s_light
{
    t_point3    origin;
    t_color3    light_color;
    double      bright_ratio;
};

struct s_hit_record
{
    t_point3    p;
    t_vec3      normal;
    double      tmin;
    double      tmax;
    double      t;
    t_bool      front_face;
	t_color3    albedo;
};

# define MAP_SIZE 4096
struct  s_scene
{
    t_canvas        canvas;
    t_camera        camera;
    t_object        *world;
    t_object        *light;
    t_color3        ambient;
    t_ray           ray;
    t_hit_record    rec;
	unsigned int	rand_map[MAP_SIZE + 1]; // 난수생성용
};

#endif