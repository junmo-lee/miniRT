#include "parse_bonus.h"

void	count_tokens_len(t_parse *parsed_struct, char **strings, int num)
{
	int	index;

	index = 0;
	while (strings[index] != NULL)
		index ++;
	if (ft_strncmp(strings[index - 1], "\n", 2) == 0)
		index --;
	if (num != index)
		parse_exit(parsed_struct);
}

void	validate_coordinate(t_parse *parsed_struct, char *str, int num)
{
	char	**xyz_tokens;

	if (str == NULL)
		parse_exit(parsed_struct);
	xyz_tokens = ft_split(str, ',');
	count_tokens_len(parsed_struct, xyz_tokens, num);
	free_tokens(xyz_tokens);
}

int	check_numeric(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isdigit(str[index]) == 0 && str[index] != ',' \
		&& str[index] != '.' && str[index] != '-' && str[index] != '+' \
		&& str[index] != '\n')
			return (-1);
		index ++;
	}
	return (0);
}

int	check_all_numeric(char **strings)
{
	int	index;

	if (strings[0] == NULL)
		return (-1);
	index = 1;
	while (strings[index] != NULL)
	{
		if (check_numeric(strings[index]) == -1)
			return (-1);
		index ++;
	}
	return (0);
}
