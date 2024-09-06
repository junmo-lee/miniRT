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
typedef struct s_plain	t_plain;
typedef struct s_cylinder	t_cylinder;
typedef	struct s_cone	t_cone;
typedef struct s_light  t_light;
typedef int             t_bool;

typedef struct s_hit_record t_hit_record;
typedef struct  s_object    t_object;

typedef	struct	s_vmlx	t_vmlx;

# define FALSE 0
# define TRUE 1

// enum 으로 바꾸어도 될듯
typedef int             t_object_type;
# define SP 0
# define LIGHT_POINT 1
# define PL 2
# define CY 3
// bonus
# define CO 4


# define EPSILON 1e-6 // 0.000001
# define LUMEN 3
// # define PI 3.14159265358979323846

# define RGB_T 0

# define SAMPLES_PER_PIXEL 4

// for mt19937
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

#define RAND_SEED 1234UL

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
	double  aspect_ratio; //종횡비 (w / h)
	double	h_fov; // horizontal fov(radian), input 값(고정)
	double	v_fov; // vertical fov(radian), 
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

/*
pl  0.0,0.0,-10.0  0.0,1.0,0.0  0,0,225
- x,y,z 좌표 : **0.0, 0.0, -10.0**
- 정규화된 삼차원 방향 벡터. 각 x, y, z 축 마다 [-1, 1] 의 범위를 가짐 : **0.0, 0.0, 1.0**
- R,G,B 색 범위 [0, 255] : **0, 0, 255**
*/
struct  s_plain
{
	t_point3    P; // 평면 위의 한 점
	t_vec3		n; // 정규화된 삼차원 방향 벡터. 각 x, y, z 축 마다 [-1, 1] 의 범위를 가짐
};

/*
cy  50.0,0.0,20.6  0.0,0.0,1.0  10,0,255  14.2  21.42
- x,y,z 좌표 : **50.0, 0.0, 20.6**
- 정규화된 삼차원 방향 벡터. 각 x, y, z 축 마다 [-1, 1] 의 범위를 가짐 : **0.0, 0.0, 1.0**
- 원기둥의 직경 : **14.2**
- 원기둥의 높이 : **21.42**
- R,G,B 색 범위 [0, 255] : **10, 0, 255***/
struct s_cylinder
{
	t_point3	center; // 중심 x,y,z 좌표
	t_vec3		n; // 정규화된 삼차원 방향 벡터 각 x, y, z 축 마다 [-1, 1] 의 범위를 가짐
	double		radius; // 원기둥의 직경
	double		height; // 원기둥의 높이
	t_vec3		h; // height * n;
	t_vec3		PC; // rootP - C
	double		PC_dot_Hhat; // check for height, PC - PC_dot_Hhat = ray->normal
};

// bonus part
struct s_cone
{
	t_point3	center; // 중심 x,y,z 좌표
	t_vec3		n; // 정규화된 삼차원 방향 벡터 각 x, y, z 축 마다 [-1, 1] 의 범위를 가짐
	double		radius; // 원뿔 밑면 반지름
	double		height; // 원뿔 높이
	t_vec3		h; // height * n;
	t_point3	H; // center + h;
	double		m; // r^2 / 2-norm(h)
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

struct  s_scene
{
    t_canvas        canvas;
    t_camera        camera;
    t_object        *world;
    t_object        *light;
    t_color3        ambient;
    t_ray           ray;
    t_hit_record    rec;
};

struct	s_vmlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_scene	*scene;
};

typedef struct s_MT19937
{
	unsigned long	mt[N];
	int				mti;
}	t_MT19937;

#endif