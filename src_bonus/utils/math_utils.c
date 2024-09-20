#include "utils_bonus.h"

double	to_degrees(double radians)
{
	return (radians * (180.0 / M_PI));
}

double	to_radians(double degrees)
{
	return (degrees / 180.0 * M_PI);
}

// double val 이 target 과 EPSILON 오차 이내인지 확인
t_bool	check_eql_double(double val, double target)
{
	return (fabs(val - target) < EPSILON);
}
