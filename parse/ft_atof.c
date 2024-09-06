#include "parse.h"

static void	ft_skip_whitespace(const char *str, int *index)
{
	while ((str[*index] != '\0') && ((str[*index] == ' ') \
	|| ((str[*index] >= 9) && (str[*index] <= 13))))
		*index += 1;
}

static int	ft_distinguish_signs(const char *str, int *index)
{
	if (str[*index] == '+')
	{
		*index += 1;
		return (1);
	}
	else if (str[*index] == '-')
	{
		*index += 1;
		return (-1);
	}
	return (1);
}

static void	ft_skip_zeros(const char *str, int *index)
{
	while ((str[*index] != '\0') && (str[*index] == '0'))
		*index += 1;
}

static void	ft_make_number(const char *str, int *index, double *result)
{
	double	factor;
	int		decimal_found;

	factor = 1.0;
	decimal_found = 0;
	while (str[*index] != '\0')
	{
		if (str[*index] >= '0' && str[*index] <= '9')
		{
			if (!decimal_found)
				*result = *result * 10 + (str[*index] - '0');
			else
			{
				factor *= 0.1;
				*result = *result + (str[*index] - '0') * factor;
			}
		}
		else if (decimal_found == 0 && str[*index] == '.')
			decimal_found = 1;
		else
			break ;
		*index += 1;
	}
}

double	ft_atof(const char *str)
{
	double	result;
	int		index;
	double	sign;

	result = 0;
	index = 0;
	ft_skip_whitespace(str, &index);
	sign = ft_distinguish_signs(str, &index);
	ft_skip_zeros(str, &index);
	ft_make_number(str, &index, &result);
	return (result * sign);
}
