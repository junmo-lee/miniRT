#include "parse.h"

int	str_num_check(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isdigit(str[index]) == 0 && str[index] != ',' && str[index] != '.' && str[index] != '-' && str[index] != '+' && str[index] != '\n')
			return (-1);
		index ++;
	}
	return (0);
}

int	strings_syntex_check(char **strings)
{
	int	index;

	if (strings[0] == NULL)
		return (-1);
	index = 1;
	while (strings[index] != NULL)
	{
		if (str_num_check(strings[index]) == -1)
			return (-1);
		index ++;
	}
	return (0);
}

void	parse(t_parse *parsed_struct, char *file_location)
{
	int			fd;
    char		*buf;
	char		**strings;

	// int	tem_index;

	buf = NULL;
	fd = open(file_location, O_RDONLY);
    if (fd == -1)
    {
        perror("fd error\n");
		return ;
    }
	while (1)
	{
		buf = get_next_line(fd);
		if (buf == NULL)
			break ;
		strings = ft_split(buf, ' ');
		if (strings_syntex_check(strings) == -1) 
			continue ;
		classify_identifier(parsed_struct, strings);
		// tem_index = 0;
		// while (strings[tem_index] != NULL)
		// {
		// 	printf("%s ", strings[tem_index]);
		// 	tem_index ++;
		// }
		// printf("\n");
		// printf("%s\n", buf);
		// free(buf);
		// strings를 free 시켜줘야함
	}
}

int	main(int argc, char **argv)
{
	t_parse parsed_struct; // malloc을 최소화 하려함

    if (argc != 2)
    {
        printf("argument error\n");
        return (0);
    }
    else
	{
		init_t_parse(&parsed_struct);
		parse(&parsed_struct, argv[1]);
	}
    return (0);
}
