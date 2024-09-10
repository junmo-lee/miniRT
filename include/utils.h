#ifndef UTILS_H
# define UTILS_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "structures.h"

t_vec3			vec3(double x, double y, double z);
t_point3		point3(double x, double y, double z);
t_point3		color3(double r, double g, double b);
void			vset(t_vec3 *vec, double x, double y, double z);
double			vlength(t_vec3 vec);
t_vec3			vplus(t_vec3 vec, t_vec3 vec2);
t_vec3			vminus(t_vec3 vec, t_vec3 vec2);
t_vec3			vscalar(t_vec3 vec, double t);
t_vec3			vmulti(t_vec3 vec, t_vec3 vec2);
t_vec3			vdivide(t_vec3 vec, double t);
double			vdot(t_vec3 vec, t_vec3 vec2);
t_vec3			vcross(t_vec3 vec, t_vec3 vec2);
t_vec3			vunit(t_vec3 vec);

double			vangle(t_vec3 vec1, t_vec3 vec2);

void			vprint(t_vec3 vec);

// 오브젝트 유틸리티
void			oadd(t_object **list, t_object *new);
t_object		*olast(t_object *list);

// 수학 관련 추가
double			to_degrees(double radians);
double			to_radians(double degrees);
t_bool			check_eql_double(double val, double target);

void			init_genrand(t_MT19937 *state, unsigned long s);
unsigned long	genrand_int32(t_MT19937 *state);
double			grand_r3(t_MT19937 *state);
#endif