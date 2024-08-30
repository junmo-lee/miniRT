#include "utils.h"

int	gen_rand_map(unsigned int *rand_map)
{
	int		fd;
	ssize_t	read_byte;

	fd = open(RAND_DIR, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	read_byte = read(fd, rand_map, sizeof(unsigned int) * MAP_SIZE);
	close(fd);
	if (read_byte < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

double	map_rand(unsigned int *rand_map)
{
	static int	index;

	if (index >= MAP_SIZE)
		index = 0;
	return ((double)rand_map[index++] / (double)UINT32_MAX);
}